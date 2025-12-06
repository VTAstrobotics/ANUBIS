#include <memory>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <unordered_map>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "motor_messages/msg/command.hpp"
#include "motor_control/sparkmax_controller.hpp"
#include "motor_control/motor_controller_base.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>

// need to include kraken once finished

// change this
#define reaper_wheelbase 0.7

using std::placeholders::_1;
class Drive : public rclcpp::Node
{
public:
  Drive()
      : Node("drive_node")
  {
    //------------------------Publishers and Subscribers
    cmd_vel_subscriber = this->create_subscription<geometry_msgs::msg::Twist>(
        "/cmd_vel", 10, std::bind(&Drive::cmd_vel_callback, this, _1));
    left_velocity_publisher = this->create_publisher<motor_messages::msg::Command>("/front_left/control", 10);
    right_velocity_publisher = this->create_publisher<motor_messages::msg::Command>("/front_right/control", 10);
    odom_publisher = this->create_publisher<nav_msgs::msg::Odometry>("/odom", 10);

    left_feedback_subscriber = this->create_subscription<motor_messages::msg::Feedback>(
        "/front_left/status", 10, std::bind(&Drive::left_feedback_callback, this, _1));

    right_feedback_subscriber = this->create_subscription<motor_messages::msg::Feedback>(
        "/front_right/status", 10, std::bind(&Drive::right_feedback_callback, this, _1));
    //--------------------------Config logic
    this->declare_parameter<std::string>("robot", "REAPER");
    const std::string robot_name = this->get_parameter("robot").as_string();

    this->declare_parameter<double>("wheelbase", reaper_wheelbase);
    this->wheelbase = this->get_parameter("wheelbase").as_double();

    this->declare_parameter<double>("motor_gear_ratio", 125.0);
    this->motor_gear_ratio = this->get_parameter("motor_gear_ratio").as_double();

    this->declare_parameter<double>("wheel_diameter", 0.31);
    this->wheel_diameter = this->get_parameter("wheel_diameter").as_double();

    this->declare_parameter<double>("odom_update_rate", 50.0); // Hz. Theoretically higher is better but our motors only update so quickly
    this->odom_update_rate = this->get_parameter("odom_update_rate").as_double();

    if (robot_name == "REAPER")
    {

      wheelbase = reaper_wheelbase;
      auto left_motor = rclcpp::NodeOptions()
                            .append_parameter_override("motor_name", "left_motor")
                            .append_parameter_override("can_interface", "can1")
                            .append_parameter_override("can_id", 11)
                            .append_parameter_override("control_topic", "/front_left/control")
                            .append_parameter_override("status_topic", "/front_left/status")
                            .append_parameter_override("health_topic", "/front_left/health")
                            .arguments({"--ros-args", "-r", "__node:=left_motor_controller"}); // should prevent naming overlap

      auto left = std::make_shared<SparkMaxController>(left_motor);

      left_motors.push_back(left);

      auto right_motor = rclcpp::NodeOptions()
                             .append_parameter_override("motor_name", "right_motor")
                             .append_parameter_override("can_interface", "can1")
                             .append_parameter_override("can_id", 10)
                             .append_parameter_override("control_topic", "/front_right/control")
                             .append_parameter_override("status_topic", "/front_right/status")
                             .append_parameter_override("health_topic", "/front_right/health")
                             .arguments({"--ros-args", "-r", "__node:=right_motor_controller"});
      auto right = std::make_shared<SparkMaxController>(right_motor);
      right_motors.push_back(right);
      RCLCPP_INFO(this->get_logger(), "Creating Drive REAPER");
      RCLCPP_INFO(this->get_logger(), "Creating Drive REAPER");
    }
    else if (robot_name == "ANUBIS")
    {
      // fill this in after ANUBIS has been constructed
    }
    else
    {
      RCLCPP_ERROR(this->get_logger(), "Robot name not recognized. Please set robot parameter");
    }
    //------------------------Timers
    int64_t odom_period_ms = 1000 * (1.0 / odom_update_rate);
    this->odom_timer = this->create_wall_timer(
        std::chrono::milliseconds(odom_period_ms),
        std::bind(&Drive::update_odometry, this));
  }

  /**
   * Add motor node instances to exec
   */
  void add_motors(const std::shared_ptr<rclcpp::Executor> &exec)
  {
    for (auto &n : left_motors)
    {
      exec->add_node(n);
    }
    for (auto &n : right_motors)
    {
      exec->add_node(n);
    }
  }

private:
  struct pose2d // https://www.ros.org/reps/rep-0103.html
  {
    double x;          // meter
    double y;          // meter
    double theta;      // radian counter clockwise positive
    rclcpp::Time time; // seconds(what time was this pose recorded at)
  };

  struct velocity2d
  {
    double linear;    // meters per second
    double angular_z; //(yaw) radian per second
  };

  /**
   * reacts to /cmd_velocity message, and distrubutes velocity to left_right topics
   */
  void cmd_vel_callback(geometry_msgs::msg::Twist::SharedPtr msg)
  {
    double lin_x = msg->linear.x;
    double ang_z = msg->angular.z;

    RCLCPP_INFO(this->get_logger(), "Driving With cmd_vel/");

    // velocity control
    float left_vel = (lin_x - 0.5 * ang_z * wheelbase);
    float right_vel = -(lin_x + 0.5 * ang_z * wheelbase);
    std::cout << "VELOCITY: " << left_vel << " | " << right_vel << std::endl;
    float left_rpm = (left_vel / ((wheel_diameter) / 2)) * 60 / (2 * M_PI) * motor_gear_ratio;
    float right_rpm = (right_vel / ((wheel_diameter) / 2)) * (60 / (2 * M_PI)) * motor_gear_ratio;

    std::cout << "RPM: " << left_rpm << " | " << right_rpm << "\n"
              << std::endl;

    // double left_vel = lin_x - ang_z;
    // double right_vel = lin_x + ang_z;

    motor_messages::msg::Command right_velocity_msg;
    motor_messages::msg::Command left_velocity_msg;

    left_velocity_msg.velocity.data = left_rpm;
    right_velocity_msg.velocity.data = right_rpm;

    left_velocity_publisher->publish(left_velocity_msg);
    right_velocity_publisher->publish(right_velocity_msg);
  }

  pose2d integrate_velocity(pose2d current_pose, velocity2d vel)
  {
    pose2d new_pose;
    new_pose.x = 0;
    new_pose.y = 0;
    new_pose.theta = 0;
    new_pose.time = this->now();
    new_pose.x = 0;
    new_pose.y = 0;
    new_pose.theta = 0;
    new_pose.time = this->now();
    double dt = (this->now() - current_pose.time).seconds();
    RCLCPP_INFO(this->get_logger(), "Creating Drive REAPER");
    RCLCPP_INFO(this->get_logger(), "Creating Drive REAPER");
    if (dt < 0)
    {
      RCLCPP_ERROR(this->get_logger(), "Time went backwards somehow in odometry integration");
      dt = 0; // just dont change the state estimate
    }
    if (dt > 2 * (1 / odom_update_rate))
    {
      RCLCPP_WARN(this->get_logger(), "Large dt detected in odometry integration: %f seconds", dt);
    }

    double linear_x = vel.linear * cos(current_pose.theta);
    double linear_y = vel.linear * sin(current_pose.theta);
    new_pose.x = current_pose.x + linear_x * dt;
    new_pose.y = current_pose.y + linear_y * dt;
    ;
    new_pose.theta = current_pose.theta + vel.angular_z * dt;
    return new_pose;
  }

  // TODO: when IMU is added make these work for an arbitrary number of motors
  void left_feedback_callback(motor_messages::msg::Feedback::SharedPtr msg)
  {
    std::string motor_name = "front_left";
    RCLCPP_INFO(this->get_logger(), "Updating Left Motor");
    odom_mutex.lock();
    last_left_feedback = msg;
    left_velocity[motor_name] = msg->velocity.data * (M_PI * wheel_diameter) / motor_gear_ratio;
    odom_mutex.unlock();
  }

  void right_feedback_callback(motor_messages::msg::Feedback::SharedPtr msg)
  {
    std::string motor_name = "front_right";
    RCLCPP_INFO(this->get_logger(), "Updating Right Motor");
    odom_mutex.lock();
    last_right_feedback = msg;
    right_velocity[motor_name] = -msg->velocity.data * (M_PI * wheel_diameter) / motor_gear_ratio;
    odom_mutex.unlock();
  }

  void update_odometry()
  {
    RCLCPP_INFO(this->get_logger(), "Updating Odom");
    velocity2d current_velocity{0.0, 0.0};
    odom_mutex.lock();
    if ((last_left_feedback != nullptr) && (last_right_feedback != nullptr))
    {
      if ((last_left_feedback != nullptr) && (last_right_feedback != nullptr))
      {
        current_velocity.linear = (last_left_feedback->velocity.data + (-last_right_feedback->velocity.data)) / 2.0;
        current_velocity.angular_z = ((-last_right_feedback->velocity.data) - last_left_feedback->velocity.data) / wheelbase;
        current_pose = integrate_velocity(current_pose, current_velocity);
      }
      publish_odometry();

      odom_mutex.unlock();
    }
  }

  void publish_odometry()
  {
    nav_msgs::msg::Odometry odom_msg;
    odom_msg.header.stamp = this->now();
    odom_msg.header.frame_id = "odom";
    odom_msg.child_frame_id = "base_link";
    odom_msg.pose.pose.position.x = current_pose.x;
    odom_msg.pose.pose.position.y = current_pose.y;
    odom_msg.pose.pose.position.z = 0.0; // no flying here

    odom_msg.pose.pose.orientation = tf2::toMsg(
        tf2::Quaternion(0, 0, sin(current_pose.theta / 2.0), cos(current_pose.theta / 2.0)));

    odom_msg.twist.twist.linear.x = current_velocity.linear * cos(current_pose.theta);
    odom_msg.twist.twist.linear.y = current_velocity.linear * sin(current_pose.theta);
    odom_msg.twist.twist.linear.z = 0.0; // no upwards movement
    odom_msg.twist.twist.angular.z = current_velocity.angular_z;

    odom_publisher->publish(odom_msg);
    RCLCPP_INFO(this->get_logger(), "Publishing Odom");
  }

  //----------------------publishers/subscribers
  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_subscriber;
  rclcpp::Publisher<motor_messages::msg::Command>::SharedPtr left_velocity_publisher;
  rclcpp::Publisher<motor_messages::msg::Command>::SharedPtr right_velocity_publisher;
  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_publisher;

  std::vector<rclcpp::Subscription<motor_messages::msg::Feedback>::SharedPtr> left_feedback_subscribers;
  std::vector<rclcpp::Subscription<motor_messages::msg::Feedback>::SharedPtr> right_feedback_subscribers;

  rclcpp::Subscription<motor_messages::msg::Feedback>::SharedPtr left_feedback_subscriber;
  rclcpp::Subscription<motor_messages::msg::Feedback>::SharedPtr right_feedback_subscriber;
  //------------------------Timer
  rclcpp::TimerBase::SharedPtr odom_timer;

  //------------------------data variables
  std::vector<std::shared_ptr<rclcpp::Node>> left_motors;
  std::vector<std::shared_ptr<rclcpp::Node>> right_motors;

  std::unordered_map<std::string, double> left_velocity;  // currently unused but will be needed for multi motor
  std::unordered_map<std::string, double> right_velocity; // currently unused but will be needed for multi motor

  double wheelbase; // in meters
  double motor_gear_ratio;
  double wheel_diameter; // in meters

  /**
   * These are used to update the odometry and ensure that things are synchronized ish hopefully
   * IDK i'm not a multithreading expert
   */

  motor_messages::msg::Feedback::SharedPtr last_left_feedback; // temps for the single motor config
  motor_messages::msg::Feedback::SharedPtr last_right_feedback;

  std::mutex odom_mutex;
  pose2d current_pose{0.0, 0.0, 0.0, this->now()};
  velocity2d current_velocity{0.0, 0.0};
  double odom_update_rate; // Hz
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  auto exec = std::make_shared<rclcpp::executors::MultiThreadedExecutor>();
  auto drive = std::make_shared<Drive>();
  exec->add_node(drive);
  drive->add_motors(exec);
  exec->spin();
  rclcpp::shutdown();
  return 0;
}
