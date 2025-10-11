#pragma once

#include <rclcpp/rclcpp.hpp>
#include "motor_messages/msg/command.hpp"
#include "motor_messages/msg/feedback.hpp"
#include "motor_messages/msg/health.hpp"

namespace motor_control {

class MotorControllerBase : public rclcpp::Node
{
public:
  explicit MotorControllerBase(const rclcpp::NodeOptions & options = rclcpp::NodeOptions())
  : rclcpp::Node("motor_controller_base",options)
  { 
    this->declare_parameter<std::string>("motor_name", "default_motor");
    this->declare_parameter<std::string>("control_topic", "/speed");
  }

  virtual void control_callback(const motor_messages::msg::Command::SharedPtr msg) = 0;
  virtual void publish_status(const motor_messages::msg::Feedback::SharedPtr msg) = 0;
  virtual void publish_health(const motor_messages::msg::Health::SharedPtr msg) = 0;

  virtual ~MotorControllerBase() = default;
};

} // namespace motor_control