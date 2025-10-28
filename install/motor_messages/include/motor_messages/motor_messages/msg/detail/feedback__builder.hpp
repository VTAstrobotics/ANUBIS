// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from motor_messages:msg/Feedback.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "motor_messages/msg/feedback.hpp"


#ifndef MOTOR_MESSAGES__MSG__DETAIL__FEEDBACK__BUILDER_HPP_
#define MOTOR_MESSAGES__MSG__DETAIL__FEEDBACK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "motor_messages/msg/detail/feedback__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace motor_messages
{

namespace msg
{

namespace builder
{

class Init_Feedback_is_disabled
{
public:
  explicit Init_Feedback_is_disabled(::motor_messages::msg::Feedback & msg)
  : msg_(msg)
  {}
  ::motor_messages::msg::Feedback is_disabled(::motor_messages::msg::Feedback::_is_disabled_type arg)
  {
    msg_.is_disabled = std::move(arg);
    return std::move(msg_);
  }

private:
  ::motor_messages::msg::Feedback msg_;
};

class Init_Feedback_position
{
public:
  explicit Init_Feedback_position(::motor_messages::msg::Feedback & msg)
  : msg_(msg)
  {}
  Init_Feedback_is_disabled position(::motor_messages::msg::Feedback::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_Feedback_is_disabled(msg_);
  }

private:
  ::motor_messages::msg::Feedback msg_;
};

class Init_Feedback_current
{
public:
  explicit Init_Feedback_current(::motor_messages::msg::Feedback & msg)
  : msg_(msg)
  {}
  Init_Feedback_position current(::motor_messages::msg::Feedback::_current_type arg)
  {
    msg_.current = std::move(arg);
    return Init_Feedback_position(msg_);
  }

private:
  ::motor_messages::msg::Feedback msg_;
};

class Init_Feedback_velocity
{
public:
  Init_Feedback_velocity()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Feedback_current velocity(::motor_messages::msg::Feedback::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_Feedback_current(msg_);
  }

private:
  ::motor_messages::msg::Feedback msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::motor_messages::msg::Feedback>()
{
  return motor_messages::msg::builder::Init_Feedback_velocity();
}

}  // namespace motor_messages

#endif  // MOTOR_MESSAGES__MSG__DETAIL__FEEDBACK__BUILDER_HPP_
