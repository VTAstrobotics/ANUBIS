// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motor_messages:msg/Command.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "motor_messages/msg/command.hpp"


#ifndef MOTOR_MESSAGES__MSG__DETAIL__COMMAND__BUILDER_HPP_
#define MOTOR_MESSAGES__MSG__DETAIL__COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motor_messages/msg/detail/command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motor_messages
{

namespace msg
{

namespace builder
{

class Init_Command_dutycycle
{
public:
  explicit Init_Command_dutycycle(::motor_messages::msg::Command & msg)
  : msg_(msg)
  {}
  ::motor_messages::msg::Command dutycycle(::motor_messages::msg::Command::_dutycycle_type arg)
  {
    msg_.dutycycle = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motor_messages::msg::Command msg_;
};

class Init_Command_position
{
public:
  explicit Init_Command_position(::motor_messages::msg::Command & msg)
  : msg_(msg)
  {}
  Init_Command_dutycycle position(::motor_messages::msg::Command::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_Command_dutycycle(msg_);
  }

private:
  ::motor_messages::msg::Command msg_;
};

class Init_Command_current
{
public:
  explicit Init_Command_current(::motor_messages::msg::Command & msg)
  : msg_(msg)
  {}
  Init_Command_position current(::motor_messages::msg::Command::_current_type arg)
  {
    msg_.current = std::move(arg);
    return Init_Command_position(msg_);
  }

private:
  ::motor_messages::msg::Command msg_;
};

class Init_Command_velocity
{
public:
  Init_Command_velocity()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Command_current velocity(::motor_messages::msg::Command::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_Command_current(msg_);
  }

private:
  ::motor_messages::msg::Command msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motor_messages::msg::Command>()
{
  return motor_messages::msg::builder::Init_Command_velocity();
}

}  // namespace motor_messages

#endif  // MOTOR_MESSAGES__MSG__DETAIL__COMMAND__BUILDER_HPP_
