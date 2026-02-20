#pragma once
#include <memory>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <unordered_map>

#include "rclcpp/rclcpp.hpp"
#include "motor_messages/msg/command.hpp"
#include "motor_control/motor_controller_base.hpp"
#include "motor.hpp"
#include "ctre/phoenix6/CANBus.hpp"
#include "ctre/phoenix6/unmanaged/Unmanaged.hpp"
#include "ctre/phoenix6/TalonFX.hpp"


enum direction{
    CLOCKWISE = 0,
    COUNTERCLOCKWISE;
};

class CanCoder
{

public:
    Cancoder(std::string can_interface,
          int can_ID, bool dir);

    float get_angle();

private:
    ctre::phoenix6::configs::CANcoderConfiguration cancoder_config;
    ctre::phoenix6::hardware::CANcoder cancoder

    
};