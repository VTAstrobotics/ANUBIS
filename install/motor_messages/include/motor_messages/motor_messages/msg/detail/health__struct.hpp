// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motor_messages:msg/Health.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "motor_messages/msg/health.hpp"


#ifndef MOTOR_MESSAGES__MSG__DETAIL__HEALTH__STRUCT_HPP_
#define MOTOR_MESSAGES__MSG__DETAIL__HEALTH__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'voltage'
// Member 'temperature'
// Member 'current'
#include "std_msgs/msg/detail/float32__struct.hpp"
// Member 'is_failed'
#include "std_msgs/msg/detail/bool__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__motor_messages__msg__Health __attribute__((deprecated))
#else
# define DEPRECATED__motor_messages__msg__Health __declspec(deprecated)
#endif

namespace motor_messages
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Health_
{
  using Type = Health_<ContainerAllocator>;

  explicit Health_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : voltage(_init),
    temperature(_init),
    current(_init),
    is_failed(_init)
  {
    (void)_init;
  }

  explicit Health_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : voltage(_alloc, _init),
    temperature(_alloc, _init),
    current(_alloc, _init),
    is_failed(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _voltage_type =
    std_msgs::msg::Float32_<ContainerAllocator>;
  _voltage_type voltage;
  using _temperature_type =
    std_msgs::msg::Float32_<ContainerAllocator>;
  _temperature_type temperature;
  using _current_type =
    std_msgs::msg::Float32_<ContainerAllocator>;
  _current_type current;
  using _is_failed_type =
    std_msgs::msg::Bool_<ContainerAllocator>;
  _is_failed_type is_failed;

  // setters for named parameter idiom
  Type & set__voltage(
    const std_msgs::msg::Float32_<ContainerAllocator> & _arg)
  {
    this->voltage = _arg;
    return *this;
  }
  Type & set__temperature(
    const std_msgs::msg::Float32_<ContainerAllocator> & _arg)
  {
    this->temperature = _arg;
    return *this;
  }
  Type & set__current(
    const std_msgs::msg::Float32_<ContainerAllocator> & _arg)
  {
    this->current = _arg;
    return *this;
  }
  Type & set__is_failed(
    const std_msgs::msg::Bool_<ContainerAllocator> & _arg)
  {
    this->is_failed = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    motor_messages::msg::Health_<ContainerAllocator> *;
  using ConstRawPtr =
    const motor_messages::msg::Health_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motor_messages::msg::Health_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motor_messages::msg::Health_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motor_messages::msg::Health_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motor_messages::msg::Health_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motor_messages::msg::Health_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motor_messages::msg::Health_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motor_messages::msg::Health_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motor_messages::msg::Health_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motor_messages__msg__Health
    std::shared_ptr<motor_messages::msg::Health_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motor_messages__msg__Health
    std::shared_ptr<motor_messages::msg::Health_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Health_ & other) const
  {
    if (this->voltage != other.voltage) {
      return false;
    }
    if (this->temperature != other.temperature) {
      return false;
    }
    if (this->current != other.current) {
      return false;
    }
    if (this->is_failed != other.is_failed) {
      return false;
    }
    return true;
  }
  bool operator!=(const Health_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Health_

// alias to use template instance with default allocator
using Health =
  motor_messages::msg::Health_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace motor_messages

#endif  // MOTOR_MESSAGES__MSG__DETAIL__HEALTH__STRUCT_HPP_
