// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from motor_messages:msg/Command.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "motor_messages/msg/command.h"


#ifndef MOTOR_MESSAGES__MSG__DETAIL__COMMAND__STRUCT_H_
#define MOTOR_MESSAGES__MSG__DETAIL__COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'velocity'
// Member 'current'
// Member 'position'
// Member 'dutycycle'
#include "std_msgs/msg/detail/float32__struct.h"

/// Struct defined in msg/Command in the package motor_messages.
/**
  * set only one of these fields for controlling a motor
 */
typedef struct motor_messages__msg__Command
{
  std_msgs__msg__Float32 velocity;
  std_msgs__msg__Float32 current;
  std_msgs__msg__Float32 position;
  std_msgs__msg__Float32 dutycycle;
} motor_messages__msg__Command;

// Struct for a sequence of motor_messages__msg__Command.
typedef struct motor_messages__msg__Command__Sequence
{
  motor_messages__msg__Command * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} motor_messages__msg__Command__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MOTOR_MESSAGES__MSG__DETAIL__COMMAND__STRUCT_H_
