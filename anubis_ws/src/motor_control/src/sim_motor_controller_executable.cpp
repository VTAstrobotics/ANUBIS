#include "motor_control/sim_motor_controller.hpp"
#include <rclcpp/rclcpp.hpp>

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<motor_control::SimMotorController>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
