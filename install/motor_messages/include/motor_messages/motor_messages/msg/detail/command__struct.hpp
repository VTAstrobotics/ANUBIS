// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motor_messages:msg/Command.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "motor_messages/msg/command.hpp"


#ifndef MOTOR_MESSAGES__MSG__DETAIL__COMMAND__STRUCT_HPP_
#define MOTOR_MESSAGES__MSG__DETAIL__COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'velocity'
// Member 'current'
// Member 'position'
// Member 'dutycycle'
#include "std_msgs/msg/detail/float32__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__motor_messages__msg__Command __attribute__((deprecated))
#else
# define DEPRECATED__motor_messages__msg__Command __declspec(deprecated)
#endif

namespace motor_messages
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Command_
{
  using Type = Command_<ContainerAllocator>;

  explicit Command_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : velocity(_init),
    current(_init),
    position(_init),
    dutycycle(_init)
  {
    (void)_init;
  }

  explicit Command_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : velocity(_alloc, _init),
    current(_alloc, _init),
    position(_alloc, _init),
    dutycycle(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _velocity_type =
    std_msgs::msg::Float32_<ContainerAllocator>;
  _velocity_type velocity;
  using _current_type =
    std_msgs::msg::Float32_<ContainerAllocator>;
  _current_type current;
  using _position_type =
    std_msgs::msg::Float32_<ContainerAllocator>;
  _position_type position;
  using _dutycycle_type =
    std_msgs::msg::Float32_<ContainerAllocator>;
  _dutycycle_type dutycycle;

  // setters for named parameter idiom
  Type & set__velocity(
    const std_msgs::msg::Float32_<ContainerAllocator> & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__current(
    const std_msgs::msg::Float32_<ContainerAllocator> & _arg)
  {
    this->current = _arg;
    return *this;
  }
  Type & set__position(
    const std_msgs::msg::Float32_<ContainerAllocator> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__dutycycle(
    const std_msgs::msg::Float32_<ContainerAllocator> & _arg)
  {
    this->dutycycle = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    motor_messages::msg::Command_<ContainerAllocator> *;
  using ConstRawPtr =
    const motor_messages::msg::Command_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motor_messages::msg::Command_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motor_messages::msg::Command_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motor_messages::msg::Command_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motor_messages::msg::Command_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motor_messages::msg::Command_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motor_messages::msg::Command_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motor_messages::msg::Command_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motor_messages::msg::Command_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motor_messages__msg__Command
    std::shared_ptr<motor_messages::msg::Command_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motor_messages__msg__Command
    std::shared_ptr<motor_messages::msg::Command_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Command_ & other) const
  {
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->current != other.current) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->dutycycle != other.dutycycle) {
      return false;
    }
    return true;
  }
  bool operator!=(const Command_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Command_

// alias to use template instance with default allocator
using Command =
  motor_messages::msg::Command_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace motor_messages

#endif  // MOTOR_MESSAGES__MSG__DETAIL__COMMAND__STRUCT_HPP_
