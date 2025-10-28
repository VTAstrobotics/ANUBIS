// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from motor_messages:msg/Feedback.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "motor_messages/msg/feedback.hpp"


#ifndef MOTOR_MESSAGES__MSG__DETAIL__FEEDBACK__TRAITS_HPP_
#define MOTOR_MESSAGES__MSG__DETAIL__FEEDBACK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "motor_messages/msg/detail/feedback__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'velocity'
// Member 'current'
// Member 'position'
#include "std_msgs/msg/detail/float32__traits.hpp"
// Member 'is_disabled'
#include "std_msgs/msg/detail/bool__traits.hpp"

namespace motor_messages
{

namespace msg
{

inline void to_flow_style_yaml(
  const Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: velocity
  {
    out << "velocity: ";
    to_flow_style_yaml(msg.velocity, out);
    out << ", ";
  }

  // member: current
  {
    out << "current: ";
    to_flow_style_yaml(msg.current, out);
    out << ", ";
  }

  // member: position
  {
    out << "position: ";
    to_flow_style_yaml(msg.position, out);
    out << ", ";
  }

  // member: is_disabled
  {
    out << "is_disabled: ";
    to_flow_style_yaml(msg.is_disabled, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "velocity:\n";
    to_block_style_yaml(msg.velocity, out, indentation + 2);
  }

  // member: current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current:\n";
    to_block_style_yaml(msg.current, out, indentation + 2);
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position:\n";
    to_block_style_yaml(msg.position, out, indentation + 2);
  }

  // member: is_disabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_disabled:\n";
    to_block_style_yaml(msg.is_disabled, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Feedback & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace motor_messages

namespace rosidl_generator_traits
{

[[deprecated("use motor_messages::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const motor_messages::msg::Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  motor_messages::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use motor_messages::msg::to_yaml() instead")]]
inline std::string to_yaml(const motor_messages::msg::Feedback & msg)
{
  return motor_messages::msg::to_yaml(msg);
}

template<>
inline const char * data_type<motor_messages::msg::Feedback>()
{
  return "motor_messages::msg::Feedback";
}

template<>
inline const char * name<motor_messages::msg::Feedback>()
{
  return "motor_messages/msg/Feedback";
}

template<>
struct has_fixed_size<motor_messages::msg::Feedback>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Bool>::value && has_fixed_size<std_msgs::msg::Float32>::value> {};

template<>
struct has_bounded_size<motor_messages::msg::Feedback>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Bool>::value && has_bounded_size<std_msgs::msg::Float32>::value> {};

template<>
struct is_message<motor_messages::msg::Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MOTOR_MESSAGES__MSG__DETAIL__FEEDBACK__TRAITS_HPP_
