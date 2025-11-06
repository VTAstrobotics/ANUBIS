#include <memory>
#include "settings.h"

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/float64.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "map.h"


using std::placeholders::_1;
class Distributor : public rclcpp::Node
{
  public:
    Distributor()
    : Node("Distributor_node") //name of the node
    {

      joy_subscriber = this->create_subscription<sensor_msgs::msg::Joy>( // Creating the subscriber to the Joy topic
      "/joy", 10, std::bind(&Distributor::joy_callback, this, _1)); 

      velocity_publisher = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10); // creates the publisher to the /joy topic
      // uses the joy_callback to recieve the message from the subscriber and publish it to the /joy topic

      this->declare_parameter("TRANSLATION_CONTROL", "LSTICKY");
      this->declare_parameter("ROTATION_CONTROL", "RSTICKX");
      this->declare_parameter("CONVEYOR_FORWARD", "BUTTON_B");
      this->declare_parameter("CONVEYOR_REVERSE", "BUTTON_A");
      this->declare_parameter("LINEAR_SCALE", 0.6);
      this->declare_parameter("ANGULAR_SCALE", 1.8);
      TRANSLATION_CONTROL = this->get_parameter("TRANSLATION_CONTROL").as_string();
      ROTATION_CONTROL = this->get_parameter("ROTATION_CONTROL").as_string();
      CONVEYOR_FORWARD = this->get_parameter("CONVEYOR_FORWARD").as_string();
      CONVEYOR_REVERSE = this->get_parameter("CONVEYOR_REVERSE").as_string();
      linear_scale = this->get_parameter("LINEAR_SCALE").as_double();
      angular_scale = this->get_parameter("ANGULAR_SCALE").as_double();

      RCLCPP_DEBUG(this->get_logger(), "Translation Control parameter: %s", TRANSLATION_CONTROL.c_str());
      RCLCPP_DEBUG(this->get_logger(), "Rotation Control parameter: %s", ROTATION_CONTROL.c_str());
      RCLCPP_DEBUG(this->get_logger(), "Conveyor Forward parameter: %s", CONVEYOR_FORWARD.c_str());
      RCLCPP_DEBUG(this->get_logger(), "Conveyor Reverse parameter: %s", CONVEYOR_REVERSE.c_str());
    }

  private:
    void joy_callback(sensor_msgs::msg::Joy::SharedPtr msg)
    {

        double lin = msg->axes[controls.at(TRANSLATION_CONTROL)] * linear_scale; 
        double ang = msg->buttons[controls.at(ROTATION_CONTROL)] * angular_scale;

        geometry_msgs::msg::Twist cmd; //create a variable of type Twist to hold the velocity
        cmd.linear.x = lin; //assigning the linear x vlaue to lin
        cmd.angular.z = ang; //assigning the angular z value to ang
        velocity_publisher->publish(cmd); //publishing the cmd variable to the /cmd_vel topic
 
    }
    double linear_scale = 0.6;
    double angular_scale = 1.8;
    //this is where you can declare subscribers/publishers.
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_publisher; 
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_subscriber;
    std::string TRANSLATION_CONTROL;
    std::string ROTATION_CONTROL;
    std::string CONVEYOR_FORWARD;
    std::string CONVEYOR_REVERSE;
    
    
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv); 
  rclcpp::spin(std::make_shared<Distributor>());
  rclcpp::shutdown();
  return 0;
}