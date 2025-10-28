// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motor_messages:msg/Health.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "motor_messages/msg/health.hpp"


#ifndef MOTOR_MESSAGES__MSG__DETAIL__HEALTH__BUILDER_HPP_
#define MOTOR_MESSAGES__MSG__DETAIL__HEALTH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motor_messages/msg/detail/health__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motor_messages
{

namespace msg
{

namespace builder
{

class Init_Health_is_failed
{
public:
  explicit Init_Health_is_failed(::motor_messages::msg::Health & msg)
  : msg_(msg)
  {}
  ::motor_messages::msg::Health is_failed(::motor_messages::msg::Health::_is_failed_type arg)
  {
    msg_.is_failed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motor_messages::msg::Health msg_;
};

class Init_Health_current
{
public:
  explicit Init_Health_current(::motor_messages::msg::Health & msg)
  : msg_(msg)
  {}
  Init_Health_is_failed current(::motor_messages::msg::Health::_current_type arg)
  {
    msg_.current = std::move(arg);
    return Init_Health_is_failed(msg_);
  }

private:
  ::motor_messages::msg::Health msg_;
};

class Init_Health_temperature
{
public:
  explicit Init_Health_temperature(::motor_messages::msg::Health & msg)
  : msg_(msg)
  {}
  Init_Health_current temperature(::motor_messages::msg::Health::_temperature_type arg)
  {
    msg_.temperature = std::move(arg);
    return Init_Health_current(msg_);
  }

private:
  ::motor_messages::msg::Health msg_;
};

class Init_Health_voltage
{
public:
  Init_Health_voltage()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Health_temperature voltage(::motor_messages::msg::Health::_voltage_type arg)
  {
    msg_.voltage = std::move(arg);
    return Init_Health_temperature(msg_);
  }

private:
  ::motor_messages::msg::Health msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motor_messages::msg::Health>()
{
  return motor_messages::msg::builder::Init_Health_voltage();
}

}  // namespace motor_messages

#endif  // MOTOR_MESSAGES__MSG__DETAIL__HEALTH__BUILDER_HPP_
