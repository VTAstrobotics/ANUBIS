// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from motor_messages:msg/Feedback.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "motor_messages/msg/feedback.hpp"


#ifndef MOTOR_MESSAGES__MSG__DETAIL__FEEDBACK__STRUCT_HPP_
#define MOTOR_MESSAGES__MSG__DETAIL__FEEDBACK__STRUCT_HPP_

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
#include "std_msgs/msg/detail/float32__struct.hpp"
// Member 'is_disabled'
#include "std_msgs/msg/detail/bool__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__motor_messages__msg__Feedback __attribute__((deprecated))
#else
# define DEPRECATED__motor_messages__msg__Feedback __declspec(deprecated)
#endif

namespace motor_messages
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Feedback_
{
  using Type = Feedback_<ContainerAllocator>;

  explicit Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : velocity(_init),
    current(_init),
    position(_init),
    is_disabled(_init)
  {
    (void)_init;
  }

  explicit Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : velocity(_alloc, _init),
    current(_alloc, _init),
    position(_alloc, _init),
    is_disabled(_alloc, _init)
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
  using _is_disabled_type =
    std_msgs::msg::Bool_<ContainerAllocator>;
  _is_disabled_type is_disabled;

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
  Type & set__is_disabled(
    const std_msgs::msg::Bool_<ContainerAllocator> & _arg)
  {
    this->is_disabled = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    motor_messages::msg::Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const motor_messages::msg::Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<motor_messages::msg::Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<motor_messages::msg::Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      motor_messages::msg::Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<motor_messages::msg::Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      motor_messages::msg::Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<motor_messages::msg::Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<motor_messages::msg::Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<motor_messages::msg::Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__motor_messages__msg__Feedback
    std::shared_ptr<motor_messages::msg::Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__motor_messages__msg__Feedback
    std::shared_ptr<motor_messages::msg::Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Feedback_ & other) const
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
    if (this->is_disabled != other.is_disabled) {
      return false;
    }
    return true;
  }
  bool operator!=(const Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Feedback_

// alias to use template instance with default allocator
using Feedback =
  motor_messages::msg::Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace motor_messages

#endif  // MOTOR_MESSAGES__MSG__DETAIL__FEEDBACK__STRUCT_HPP_
