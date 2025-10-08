#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/float64.hpp"


using std::placeholders::_1;
/**
 * YOUR OBJECTIVE - subscribe to the /cmd_vel topic, and publish a velocity to /left_drive and /right_drive
 * according to the velocity (assume a tank drive robot). Finish all of the TODOs in the code!
 * 
 * MESSAGE TYPES
 * SUBSCRIPTIONS
 *  * /cmd_vel (geometry_msgs/msg/Twist) 
 * PUBLISHERS
 *   /left_drive  (std_msgs/msg/Float64)
 *   /right_drive (std_msgs/msg/Float64)

 * 
 * 
 * use these equations, which are standard for a tank drive robot (assume a wheelbase of 1 meter):
 * 
 * Left Velocity = Linear Velocity x - 0.5 * Angular Velocity z * Wheelbase
 * 
 * Right Velocity = Linear Velocity x + 0.5 * Angular Velocity z * Wheelbase.
 * 
 * 
 * 
 */
class Distributor : public rclcpp::Node
{
  public:
    Distributor()
    : Node("Distributor_node") //name of the node
    {
      //this is where you assign subscribers and publishers to a topic.

      joy_subscriber = this->create_subscription<sensor_msgs::msg::Joy>( // Creating the subscriber to the Joy topic
      "/joy", 10, std::bind(&Distributor::your_callback, this, _1)); //TODO(2), change topic so subscriber listens to /joy topic.

      velocity_publisher = this->create_publisher<geometry_msgs::msg::Twist>
      ("/cmd_vel", 10, std::bind(&Distributor::joy_callback, this, _1)) // creates the publisher to the /joy topic
      // uses the joy_callback to recieve the message from the subscriber and publish it to the /joy topic
    }

  private:
    void joy_callback(sensor_msgs::msg::Joy::SharedPtr msg)
    {

        double lin = msg->axes[1] * linear_scale; // this is how you get the x velocity from the message. Try angular z!
        double ang = msg->axes[0] * angular_scale; //the angular variable

        geometry_msgs::msg::Twist cmd; //create a variable of type Twist to hold the velocity
        cmd.linear.x = lin; //assigning the linear x vlaue to lin
        cmd.angular.z = ang; //assigning the angular z value to ang
        velocity_publisher->publish(cmd); //publishing the cmd variable to the /cmd_vel topic

        double linear_scale = 0.6;
        double angular_scale = 1.8;
    }
    //this is where you can declare subscribers/publishers.
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr velocity_subscriber; //note the message type (hint - TODO(1))
    rclcpp::Subscriber<std_msgs::msg::Joy>::SharedPtr joy_subscriber; // example for the /left_drive publisher. You need to make the right publisher.
    
};

int main(int argc, char * argv[])
{
  //you don't have to worry about changing any of this for now
  //this is the code that makes everything run
  rclcpp::init(argc, argv); 
  rclcpp::spin(std::make_shared<Distributor>());
  rclcpp::shutdown();
  return 0;
}