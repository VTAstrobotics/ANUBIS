#include "motor_control/motor_controller_base.hpp"
#include <rclcpp/rclcpp.hpp>
#include "motor_control/kraken_controller.hpp"




  void KrakenController::control_callback(const motor_messages::msg::Command::SharedPtr msg)
  {    
    RCLCPP_INFO(this->get_logger(), "Controlling Kraken motor with command: %f", (msg->velocity.data));
    // Implement the logic to control the Kraken motor here
    
  }