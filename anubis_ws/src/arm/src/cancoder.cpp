
#include <memory>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <unordered_map>

#include "rclcpp/rclcpp.hpp"
#include "motor_messages/msg/command.hpp"
#include "motor_control/motor_controller_base.hpp"
#include "cancoder.hpp"
#include "ctre/phoenix6/CANBus.hpp"
#include "ctre/phoenix6/unmanaged/Unmanaged.hpp"
#include "ctre/phoenix6/TalonFX.hpp"

using std::placeholders::_1;

Cancoder::Cancoder(std::string can_interface,
                   int can_ID, bool dir)
{
    this->cancoder_config.MagnetSensor.SensorDirection = (dir == CLOCKWISE) ? signals::SensorDirectionValue::Clockwise_Positive : signals::SensorDirectionValue::Clockwise_Negative;





    
}