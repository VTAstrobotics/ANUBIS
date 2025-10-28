// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from motor_messages:msg/Health.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "motor_messages/msg/health.hpp"


#ifndef MOTOR_MESSAGES__MSG__DETAIL__HEALTH__TRAITS_HPP_
#define MOTOR_MESSAGES__MSG__DETAIL__HEALTH__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "motor_messages/msg/detail/health__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'voltage'
// Member 'temperature'
// Member 'current'
#include "std_msgs/msg/detail/float32__traits.hpp"
// Member 'is_failed'
#include "std_msgs/msg/detail/bool__traits.hpp"

namespace motor_messages
{

namespace msg
{

inline void to_flow_style_yaml(
  const Health & msg,
  std::ostream & out)
{
  out << "{";
  // member: voltage
  {
    out << "voltage: ";
    to_flow_style_yaml(msg.voltage, out);
    out << ", ";
  }

  // member: temperature
  {
    out << "temperature: ";
    to_flow_style_yaml(msg.temperature, out);
    out << ", ";
  }

  // member: current
  {
    out << "current: ";
    to_flow_style_yaml(msg.current, out);
    out << ", ";
  }

  // member: is_failed
  {
    out << "is_failed: ";
    to_flow_style_yaml(msg.is_failed, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Health & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "voltage:\n";
    to_block_style_yaml(msg.voltage, out, indentation + 2);
  }

  // member: temperature
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "temperature:\n";
    to_block_style_yaml(msg.temperature, out, indentation + 2);
  }

  // member: current
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current:\n";
    to_block_style_yaml(msg.current, out, indentation + 2);
  }

  // member: is_failed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_failed:\n";
    to_block_style_yaml(msg.is_failed, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Health & msg, bool use_flow_style = false)
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
  const motor_messages::msg::Health & msg,
  std::ostream & out, size_t indentation = 0)
{
  motor_messages::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use motor_messages::msg::to_yaml() instead")]]
inline std::string to_yaml(const motor_messages::msg::Health & msg)
{
  return motor_messages::msg::to_yaml(msg);
}

template<>
inline const char * data_type<motor_messages::msg::Health>()
{
  return "motor_messages::msg::Health";
}

template<>
inline const char * name<motor_messages::msg::Health>()
{
  return "motor_messages/msg/Health";
}

template<>
struct has_fixed_size<motor_messages::msg::Health>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Bool>::value && has_fixed_size<std_msgs::msg::Float32>::value> {};

template<>
struct has_bounded_size<motor_messages::msg::Health>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Bool>::value && has_bounded_size<std_msgs::msg::Float32>::value> {};

template<>
struct is_message<motor_messages::msg::Health>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MOTOR_MESSAGES__MSG__DETAIL__HEALTH__TRAITS_HPP_
