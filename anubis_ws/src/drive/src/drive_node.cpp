#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/float64.hpp"
#include "sensor_msgs/msg/joy.hpp"

 //change this

#define reaper_wheelbase 100;

using std::placeholders::_1;
class Drive : public rclcpp::Node
{
  public:
    Drive()
    : Node("drive_node") 
    {
        //------------------------Publishers and Subscribers
        cmd_vel_subscriber = this->create_subscription<geometry_msgs::msg::Twist>( 
        "/cmd_vel", 10, std::bind(&Distributor::cmd_vel_callback, this, _1)); 
        left_velocity_publisher = this->create_publisher<motor_messages::msg::Command>("/front_left/control", 10);
        right_velocity_publisher = this->create_publisher<motor_messages::msg::Command>("/front_right/control", 10);

        //--------------------------Config logic
        String my_param = this->get_parameter("robot").as_int();
        
        if(my_param == "REAPER"){
            wheelbase = reaper_wheelbase;
            auto left_motor = rclcpp::NodeOptions()
                .append_parameter_override("can_interface", "can0")
                .append_parameter_override("can_id", 1)
                .append_parameter_override("control_topic", "/front_left/control")
                .append_parameter_override("status_topic",  "/front_left/status")
                .append_parameter_override("health_topic",  "/front_left/health")

            auto left = std::make_shared<KrakenController>(left_motor);
            motors.push_back(left);

            auto right_motor = rclcpp::NodeOptions()
                .append_parameter_override("can_interface", "can1")
                .append_parameter_override("can_id", 1)
                .append_parameter_override("control_topic", "/front_right/control")
                .append_parameter_override("status_topic",  "/front_right/status")
                .append_parameter_override("health_topic",  "/front_right/health")

            auto right = std::make_shared<KrakenController(right_motor);
            motors.push_back(right);

        }
        else if(my_param == "ANUBIS"){
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
        int lin_x = msg->linear.x;
        int ang_z = msg->angular.z;

        float left_vel = lin_x - 0.5*ang_z * wheelbase;
        float right_vel = linx + 0.5*ang_z * wheelbase;

        motor_messages::msg::Command right_velocity_msg;
        motor_messages::msg::Command left_velocity_msg;

        left_velocity.data.velocity = right_vel;
        right_velocity.data.velocity = left_vel;
        left_publisher->publish(left_velocity_msg);
        right_publisher->publish(right_velocity_msg);
    }

    //----------------------publishers/subscribers
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_subscriber;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr left_velocity_publisher;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr right_velocity_publisher; 

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