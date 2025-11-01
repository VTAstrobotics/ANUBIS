#include <memory>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "motor_messages/msg/command.hpp"
#include "motor_control/sparkmax_controller.hpp" 
//need to include kraken once finished

 //change this
#define reaper_wheelbase 0.5

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

        //--------------------------Config logic
        this->declare_parameter<std::string>("robot", "REAPER");
        const std::string robot_name = this->get_parameter("robot").as_string();
        
        if(robot_name == "REAPER"){

          //Might have name overlap with left and right motor nodes.
            wheelbase = reaper_wheelbase;
            auto left_motor = rclcpp::NodeOptions()
                .append_parameter_override("motor_name", "left_motor")
                .append_parameter_override("can_interface", "can0")
                .append_parameter_override("can_id", 1)
                .append_parameter_override("control_topic", "/front_left/control")
                .append_parameter_override("status_topic",  "/front_left/status")
                .append_parameter_override("health_topic",  "/front_left/health");

            auto left = std::make_shared<SparkMaxController>(left_motor);
            motors.push_back(left);

            auto right_motor = rclcpp::NodeOptions()
                .append_parameter_override("motor_name", "right_motor")
                .append_parameter_override("can_interface", "can0")
                .append_parameter_override("can_id", 1)
                .append_parameter_override("control_topic", "/front_right/control")
                .append_parameter_override("status_topic",  "/front_right/status")
                .append_parameter_override("health_topic",  "/front_right/health");
            auto right = std::make_shared<SparkMaxController>(right_motor);
            motors.push_back(right);
        }
        else if(robot_name == "ANUBIS"){
          //fill this in after ANUBIS has been constructed
        }
        else{
        }

    }

  /**
   * Add motor node instances to exec
   */
  void add_motors(const std::shared_ptr<rclcpp::Executor>& exec) {
    for (auto& n : motors) {
      exec->add_node(n);
    }
  }

  private:
    /**
     * reacts to /cmd_velocity message, and distrubutes velocity to left_right topics
     */
    void cmd_vel_callback(geometry_msgs::msg::Twist::SharedPtr msg){
        float lin_x = msg->linear.x;
        float ang_z = msg->angular.z;

        float left_vel = lin_x - 0.5*ang_z * wheelbase;
        float right_vel = lin_x + 0.5*ang_z * wheelbase;

        motor_messages::msg::Command right_velocity_msg;
        motor_messages::msg::Command left_velocity_msg;

        left_velocity_msg.velocity.data = left_vel;
        right_velocity_msg.velocity.data = right_vel;

        left_velocity_publisher->publish(left_velocity_msg);
        right_velocity_publisher->publish(right_velocity_msg);
    }

    //----------------------publishers/subscribers
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_subscriber;
    rclcpp::Publisher<motor_messages::msg::Command>::SharedPtr left_velocity_publisher;
    rclcpp::Publisher<motor_messages::msg::Command>::SharedPtr right_velocity_publisher; 

    //------------------------data variables
    std::vector<std::shared_ptr<rclcpp::Node>> motors;
    double wheelbase; // in meters
};

int main(int argc, char * argv[])
{
rclcpp::init(argc, argv);
  auto exec  = std::make_shared<rclcpp::executors::MultiThreadedExecutor>();
  auto drive = std::make_shared<Drive>();
  exec->add_node(drive);
  drive->add_motors(exec);
  exec->spin();
  rclcpp::shutdown();
  return 0;
}