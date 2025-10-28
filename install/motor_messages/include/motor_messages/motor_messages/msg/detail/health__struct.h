// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motor_messages:msg/Health.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "motor_messages/msg/health.h"


#ifndef MOTOR_MESSAGES__MSG__DETAIL__HEALTH__STRUCT_H_
#define MOTOR_MESSAGES__MSG__DETAIL__HEALTH__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'voltage'
// Member 'temperature'
// Member 'current'
#include "std_msgs/msg/detail/float32__struct.h"
// Member 'is_failed'
#include "std_msgs/msg/detail/bool__struct.h"

/// Struct defined in msg/Health in the package motor_messages.
typedef struct motor_messages__msg__Health
{
  std_msgs__msg__Float32 voltage;
  std_msgs__msg__Float32 temperature;
  std_msgs__msg__Float32 current;
  /// this is left for later so that we can add error checking inside motor classes
  std_msgs__msg__Bool is_failed;
} motor_messages__msg__Health;

// Struct for a sequence of motor_messages__msg__Health.
typedef struct motor_messages__msg__Health__Sequence
{
  motor_messages__msg__Health * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motor_messages__msg__Health__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOR_MESSAGES__MSG__DETAIL__HEALTH__STRUCT_H_
