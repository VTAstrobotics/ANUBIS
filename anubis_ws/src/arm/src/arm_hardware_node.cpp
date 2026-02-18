#include <memory>
#include <chrono>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "motor_messages/msg/command.hpp"
#include "motor_control/kraken_controller.hpp"
#include "motor_control/motor_controller_base.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

#define MAX_MOTORS 5

enum JOINT
{
  BASE,
  ELBOW,
  WRIST,
  END_EFFECTOR_LAT,
  END_EFFECTOR_LONG
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
    add_publishers_to_vector();
    joint_pos_subscriber = this->create_subscription<std_msgs::msg::Float64MultiArray>(
        "/cmd_vel", 10, std::bind(&ArmHardwareNode::joint_pos_callback, this, _1));
  }

private:
  joint_motor_publishers motor_publishers[MAX_MOTORS]; // 5 DOF, 2 motors each

  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr joint_pos_subscriber;

  void add_publishers_to_vector()
  {

    motor_publishers[BASE].left_publisher = this->create_publisher<motor_messages::msg::Command>("/base_left/control", 10);
    motor_publishers[BASE].right_publisher = this->create_publisher<motor_messages::msg::Command>("/base_right/control", 10);

    motor_publishers[ELBOW].left_publisher = this->create_publisher<motor_messages::msg::Command>("/elbow_left/control", 10);
    motor_publishers[ELBOW].right_publisher = this->create_publisher<motor_messages::msg::Command>("/elbow_right/control", 10);

    motor_publishers[WRIST].left_publisher = this->create_publisher<motor_messages::msg::Command>("/wrist_left/control", 10);
    motor_publishers[WRIST].right_publisher = this->create_publisher<motor_messages::msg::Command>("/wrist_right/control", 10);

    motor_publishers[END_EFFECTOR_LAT].left_publisher = this->create_publisher<motor_messages::msg::Command>("/end_effector__lat_left/control", 10);
    motor_publishers[END_EFFECTOR_LAT].right_publisher = this->create_publisher<motor_messages::msg::Command>("/end_effector_lat_right/control", 10);

    motor_publishers[END_EFFECTOR_LONG].left_publisher = this->create_publisher<motor_messages::msg::Command>("/end_effector__long_left/control", 10);
    motor_publishers[END_EFFECTOR_LONG].right_publisher = this->create_publisher<motor_messages::msg::Command>("/end_effector_long_right/control", 10);
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