#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"



using std::placeholders::_1;
class ArmHardwareNode : public rclcpp::Node
{
public:
  ArmHardwareNode()
      : Node("arm_hardware_node") // name of the node
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