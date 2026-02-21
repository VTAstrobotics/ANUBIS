
#include <memory>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <cmath>


#include "rclcpp/rclcpp.hpp"
#include "motor_messages/msg/command.hpp"
#include "motor_control/motor_controller_base.hpp"
#include "encoder.hpp"
#include "ctre/phoenix6/CANBus.hpp"
#include "ctre/phoenix6/core/CoreCANcoder.hpp"
#include "ctre/phoenix6/CANcoder.hpp"
#include "ctre/phoenix6/unmanaged/Unmanaged.hpp"
#include "ctre/phoenix6/TalonFX.hpp"

using std::placeholders::_1;

encoder::encoder(std::string can_interface, int can_ID, bool dir)
                   : cancoder(std::make_unique<ctre::phoenix6::hardware::CANcoder>(can_ID, can_interface))
{
    this->cancoder_config.MagnetSensor.SensorDirection = (dir == CLOCKWISE) ? ctre::phoenix6::signals::SensorDirectionValue::Clockwise_Positive : ctre::phoenix6::signals::SensorDirectionValue::CounterClockwise_Positive;
    this->cancoder_config.MagnetSensor.MagnetOffset = 0;//Needs to be measured later
}

float encoder::get_angle()
{
    return this->cancoder->GetAbsolutePosition().GetValue().value() * 2 * M_PI / 180; // Rotations to degrees
}

