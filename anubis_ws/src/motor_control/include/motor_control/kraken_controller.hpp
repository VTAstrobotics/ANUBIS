#pragma once
#include "motor_control/motor_controller_base.hpp"

#include <rclcpp/rclcpp.hpp>
class KrakenController : public motor_control::MotorControllerBase
{
public:
  explicit KrakenController(const rclcpp::NodeOptions & options = rclcpp::NodeOptions())
  : motor_control::MotorControllerBase(options){

    RCLCPP_INFO(this->get_logger(), "KrakenController node has been initialized.");
    control_subscription_ = this->create_subscription<motor_messages::msg::Command>(
      this->get_parameter("control_topic").as_string(),
      10,
      std::bind(&KrakenController::control_callback, this, std::placeholders::_1)
    );
  }


  void control_callback(const motor_messages::msg::Command::SharedPtr msg) override;

  private:
    rclcpp::Subscription<motor_messages::msg::Command>::SharedPtr control_subscription_;
};