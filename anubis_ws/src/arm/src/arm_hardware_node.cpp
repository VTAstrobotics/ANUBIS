#include <memory>
#include <chrono>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "motor_messages/msg/command.hpp"
#include "motor_control/kraken_controller.hpp"
#include "motor_control/motor_controller_base.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

#define MAX_MOTORS 5

#define RADIAN_TO_REV 0.15915494

#define BASE_JOINT_GR = 125
#define ELBOW_JOINT_GR = 108
#define END_EFFECTOR_GR = 45

enum JOINT
{
  BASE_LAT=0,
  BASE_JOINT,
  ELBOW,
  END_EFFECTOR
};

struct joint_motor_publishers
{
  rclcpp::Publisher<motor_messages::msg::Command>::SharedPtr left_publisher;
  rclcpp::Publisher<motor_messages::msg::Command>::SharedPtr right_publisher;
};

using std::placeholders::_1;
class ArmHardwareNode : public rclcpp::Node

{
public:
  ArmHardwareNode()
      : Node("arm_hardware_node") // name of the node
  {
    init_joint_motor_publishers();
    joint_pos_subscriber = this->create_subscription<std_msgs::msg::Float64MultiArray>(
        "/cmd_vel", 10, std::bind(&ArmHardwareNode::joint_pos_callback, this, _1));
  }

private:
  joint_motor_publishers motor_publishers[MAX_MOTORS]; // 5 DOF, 2 motors each

  float last_positions[MAX_MOTORS] = {0}; // assume all zeroes, can change this to init position

  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr joint_pos_subscriber;

  motor_messages::msg::Command motor_msgs[MAX_MOTORS] 

  void init_joint_motor_publishers()
  {

    motor_publishers[BASE_LAT].left_publisher = this->create_publisher<motor_messages::msg::Command>("/base_left/control", 10);
    motor_publishers[BASE_
    motor_publishers[ELBOW].left_publisher = this->create_publisher<motor_messages::msg::Command>("/elbow_left/control", 10);
    motor_publishers[ELBOW].right_publisher = this->create_publisher<motor_messages::msg::Command>("/elbow_right/control", 10);

    motor_publishers[WRIST].left_publisher = this->create_publisher<motor_messages::msg::Command>("/wrist_left/control", 10);
    motor_publishers[WRIST].right_publisher = this->create_publisher<motor_messages::msg::Command>("/wrist_right/control", 10);

    motor_publishers[END_EFFECTOR_LAT].left_publisher = this->create_publisher<motor_messages::msg::Command>("/end_effector__lat_left/control", 10);
    motor_publishers[END_EFFECTOR_LAT].right_publisher = this->create_publisher<motor_messages::msg::Command>("/end_effector_lat_right/control", 10);
    
    motor_publishers[END_EFFECTOR_LONG].left_publisher = this->create_publisher<motor_messages::msg::Command>("/end_effector__long_left/control", 10);
    motor_publishers[END_EFFECTOR_LONG].right_publisher = this->create_publisher<motor_messages::msg::Command>("/end_effector_long_right/control", 10);LAT].right_publisher = this->create_publisher<motor_messages::msg::Command>("/base_right/control", 10);
  }


  void joint_pos_callback(std_msgs::msg::Float64MultiArray::SharedPtr msg)
  {




  }
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ArmHardwareNode>());
  rclcpp::shutdown();
  return 0;
}