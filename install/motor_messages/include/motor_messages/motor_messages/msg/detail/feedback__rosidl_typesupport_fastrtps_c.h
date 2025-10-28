// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from motor_messages:msg/Feedback.idl
// generated code does not contain a copyright notice
#ifndef MOTOR_MESSAGES__MSG__DETAIL__FEEDBACK__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define MOTOR_MESSAGES__MSG__DETAIL__FEEDBACK__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "motor_messages/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "motor_messages/msg/detail/feedback__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_motor_messages
bool cdr_serialize_motor_messages__msg__Feedback(
  const motor_messages__msg__Feedback * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_motor_messages
bool cdr_deserialize_motor_messages__msg__Feedback(
  eprosima::fastcdr::Cdr &,
  motor_messages__msg__Feedback * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_motor_messages
size_t get_serialized_size_motor_messages__msg__Feedback(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_motor_messages
size_t max_serialized_size_motor_messages__msg__Feedback(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_motor_messages
bool cdr_serialize_key_motor_messages__msg__Feedback(
  const motor_messages__msg__Feedback * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_motor_messages
size_t get_serialized_size_key_motor_messages__msg__Feedback(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_motor_messages
size_t max_serialized_size_key_motor_messages__msg__Feedback(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_motor_messages
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, motor_messages, msg, Feedback)();

#ifdef __cplusplus
}
#endif

#endif  // MOTOR_MESSAGES__MSG__DETAIL__FEEDBACK__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
