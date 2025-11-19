#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"
#include "sensor_msgs/msg/joy.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class Teleop : public rclcpp::Node
{
public:
  Teleop() : Node("teleop_twist_stamped")
  {
    publisher_ = this->create_publisher<geometry_msgs::msg::TwistStamped>(
      "/servo_node/delta_twist_cmds", 10);

    joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy>(
      "/joy", 10, std::bind(&Teleop::joy_callback, this, _1));
  }

private:

  void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg)
  {
    geometry_msgs::msg::TwistStamped cmd;
    cmd.header.stamp = this->now();
    cmd.header.frame_id = "base_link";  

    cmd.twist.linear.x = msg->axes[axis_x] * linear_scale;
    cmd.twist.linear.y = msg->axes[axis_y] * linear_scale;
    cmd.twist.linear.z = msg->axes[axis_z] * linear_scale;

    cmd.twist.angular.x = 0.0;
    cmd.twist.angular.y = 0.0;
    cmd.twist.angular.z = 0.0;

    publisher_->publish(cmd);
  }

  // Scale and axis mappings
  double linear_scale = 0.4;   
  int axis_x = 0;              
  int axis_y = 1;              
  int axis_z = 4;              

  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr publisher_;
  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Teleop>());
  rclcpp::shutdown();
  return 0;
}
