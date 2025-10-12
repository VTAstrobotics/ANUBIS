#include <memory>
#include "settings.h"

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/float64.hpp"
#include "sensor_msgs/msg/joy.hpp"



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
    }

  private:
    void joy_callback(sensor_msgs::msg::Joy::SharedPtr msg)
    {

        double lin = msg->axes[AXIS_LEFTY] * linear_scale; 
        double ang = msg->axes[AXIS_LEFTX] * angular_scale; 

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
    
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv); 
  rclcpp::spin(std::make_shared<Distributor>());
  rclcpp::shutdown();
  return 0;
}