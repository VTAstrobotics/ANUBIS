#include "motor_control/motor_controller_base.hpp"
#include <rclcpp/rclcpp.hpp>
#include "motor_control/kraken_controller.hpp"
#include <ctre/phoenix6/TalonFX.hpp>




  void KrakenController::control_callback(const motor_messages::msg::Command::SharedPtr msg) 
  {    

    if(abs(msg->dutycycle.data) >= 0){
      this->outDuty.Output = msg->dutycycle.data;
      this->motor->SetControl(this->outDuty);
    }
    else if(abs(msg->current.data) >= 0){
      RCLCPP_ERROR(this->get_logger(), "We have not paid for this feature L");
    }
    else if(abs(msg->position.data) >= 0){

      this->outPosition = msg->position.data * 1.0_tr;

    }
    else{
      controls::DutyCycleOut stop{0};
      this->motor->SetControl(stop);
    }

  }

  void KrakenController::publish_status() 
  {
    
    motor_messages::msg::Feedback feedback;
    RCLCPP_INFO(this->get_logger(), "Publishing Kraken motor status");

    feedback.current.data = this->motor->GetStatorCurrent().GetValueAsDouble();
    feedback.is_disabled.data = false;
    feedback.position.data = this->motor->GetPosition().GetValueAsDouble();
    feedback.velocity.data = this->motor->GetVelocity().GetValueAsDouble();

    // Implement the logic to publish the Kraken motor status here
    status_publisher->publish(feedback);
    
  }

  void KrakenController::publish_health() 
  {
    motor_messages::msg::Health health;
    RCLCPP_INFO(this->get_logger(), "Publishing Kraken motor health");
    // Implement the logic to publish the Kraken motor health here

    health.current.data = this->motor->GetStatorCurrent().GetValueAsDouble();
    health.is_failed.data = false;
    health.temperature.data = this->motor->GetDeviceTemp().GetValueAsDouble();
    health.voltage.data = this->motor->GetSupplyVoltage().GetValueAsDouble();

    health_publisher->publish(health);
  }