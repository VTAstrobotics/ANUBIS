#include <memory>
#include <chrono>
#include <vector>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "motor_messages/msg/command.hpp"
#include "motor_messages/msg/feedback.hpp"
#include "motor_control/kraken_controller.hpp"
#include "motor_control/motor_controller_base.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

#include "motor.hpp"

#define MAX_MOTORS 4

#define RADIAN_TO_REV 0.15915494

#define BASE_LAT_GR 1
#define BASE_JOINT_GR 125
#define ELBOW_JOINT_GR 108
#define END_EFFECTOR_GR 45
float GEAR_RATIOS[4] = {BASE_LAT_GR, BASE_JOINT_GR, ELBOW_JOINT_GR, END_EFFECTOR_GR};

enum JOINT
{
  BASE_LAT = 0,
  BASE_JOINT,
  ELBOW,
  END_EFFECTOR
};

struct joint_motor_publishers
{
  rclcpp::Publisher<motor_messages::msg::Command>::SharedPtr left_publisher;
  rclcpp::Publisher<motor_messages::msg::Command>::SharedPtr right_publisher;
};

struct joint_motors
{

  std::shared_ptr<motor> left;
  std::shared_ptr<motor> right;
};

using std::placeholders::_1;
class ArmJoyControl : public rclcpp::Node
{
public:
  ArmJoyControl()
      : Node("arm_joy_control_node") // name of the node
  {

  }

private:
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ArmHardwareNode>());
  rclcpp::shutdown();
  return 0;
}