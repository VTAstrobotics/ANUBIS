#include <memory>
#include <chrono>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "motor_messages/msg/command.hpp"
#include "motor_control/kraken_controller.hpp"
#include "motor_control/motor_controller_base.hpp"




using std::placeholders::_1;
class ArmHardwareNode : public rclcpp::Node
{
public:
  ArmHardwareNode()
      : Node("arm_hardware_node") // name of the node
  {
    
  }

private:

std::vector<rclcpp::Publisher<motor_messages::msg::Command>::SharedPtr> motor_publishers;


  
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ArmHardwareNode>());
  rclcpp::shutdown();
  return 0; 
}