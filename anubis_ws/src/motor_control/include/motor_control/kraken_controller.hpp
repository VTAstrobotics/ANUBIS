#pragma once
#include "motor_control/motor_controller_base.hpp"
#include <chrono>
#include <ctre/phoenix6/TalonFX.hpp>

#include <rclcpp/rclcpp.hpp>
using namespace ctre::phoenix6;
class KrakenController : public motor_control::MotorControllerBase
{
public:
  explicit KrakenController(const rclcpp::NodeOptions &options = rclcpp::NodeOptions())
      : motor_control::MotorControllerBase(options)
  {

    RCLCPP_INFO(this->get_logger(), "KrakenController node has been initialized.");
    this->declare_parameter<std::string>("can_interface", "can0");
    this->declare_parameter<int>("can_id", 42069);
    this->control_subscription = this->create_subscription<motor_messages::msg::Command>(
        this->get_parameter("control_topic").as_string(),
        10,
        std::bind(&KrakenController::control_callback, this, std::placeholders::_1));

      std::string status_topic = this->get_parameter("status_topic").as_string();
      std::string health_topic = this->get_parameter("health_topic").as_string();
      status_publisher = this->create_publisher<motor_messages::msg::Feedback>(status_topic, 4);
      health_publisher = this->create_publisher<motor_messages::msg::Health>(health_topic, 4);

    std::string can_interface = this->get_parameter("can_interface").as_string();
    this->motor = std::make_unique<hardware::TalonFX>((int)this->get_parameter("can_id").as_int(), can_interface);

    std::chrono::duration<double> status_period(1 / this->get_parameter("status_publish_frequency").as_double()); // Defaults to seconds
    this->status_timer = this->create_wall_timer(status_period, std::bind(&KrakenController::publish_status, this));

    std::chrono::duration<double> health_period(1 / this->get_parameter("health_publish_frequency").as_double()); // Defaults to seconds
    this->health_timer = this->create_wall_timer(health_period, std::bind(&KrakenController::publish_health, this));
    


  }

  void control_callback(const motor_messages::msg::Command::SharedPtr msg) override;
  void publish_status() override;
  void publish_health() override;

private:
    std::unique_ptr<hardware::TalonFX> motor; // INIT just so that there are no warnings, this needs to be overridden



  controls::DutyCycleOut outDuty{0.0};
  controls::VelocityVoltage outVelocity{0.0_tps}; // in Turns per second
  controls::PositionVoltage outPosition{0.0_tr};
  //Current Requires a premium payment lmao 
};