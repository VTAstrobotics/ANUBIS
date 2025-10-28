// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from motor_messages:msg/Health.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "motor_messages/msg/detail/health__rosidl_typesupport_introspection_c.h"
#include "motor_messages/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "motor_messages/msg/detail/health__functions.h"
#include "motor_messages/msg/detail/health__struct.h"


// Include directives for member types
// Member `voltage`
// Member `temperature`
// Member `current`
#include "std_msgs/msg/float32.h"
// Member `voltage`
// Member `temperature`
// Member `current`
#include "std_msgs/msg/detail/float32__rosidl_typesupport_introspection_c.h"
// Member `is_failed`
#include "std_msgs/msg/bool.h"
// Member `is_failed`
#include "std_msgs/msg/detail/bool__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void motor_messages__msg__Health__rosidl_typesupport_introspection_c__Health_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  motor_messages__msg__Health__init(message_memory);
}

void motor_messages__msg__Health__rosidl_typesupport_introspection_c__Health_fini_function(void * message_memory)
{
  motor_messages__msg__Health__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember motor_messages__msg__Health__rosidl_typesupport_introspection_c__Health_message_member_array[4] = {
  {
    "voltage",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motor_messages__msg__Health, voltage),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "temperature",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motor_messages__msg__Health, temperature),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "current",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motor_messages__msg__Health, current),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "is_failed",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(motor_messages__msg__Health, is_failed),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers motor_messages__msg__Health__rosidl_typesupport_introspection_c__Health_message_members = {
  "motor_messages__msg",  // message namespace
  "Health",  // message name
  4,  // number of fields
  sizeof(motor_messages__msg__Health),
  false,  // has_any_key_member_
  motor_messages__msg__Health__rosidl_typesupport_introspection_c__Health_message_member_array,  // message members
  motor_messages__msg__Health__rosidl_typesupport_introspection_c__Health_init_function,  // function to initialize message memory (memory has to be allocated)
  motor_messages__msg__Health__rosidl_typesupport_introspection_c__Health_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t motor_messages__msg__Health__rosidl_typesupport_introspection_c__Health_message_type_support_handle = {
  0,
  &motor_messages__msg__Health__rosidl_typesupport_introspection_c__Health_message_members,
  get_message_typesupport_handle_function,
  &motor_messages__msg__Health__get_type_hash,
  &motor_messages__msg__Health__get_type_description,
  &motor_messages__msg__Health__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_motor_messages
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, motor_messages, msg, Health)() {
  motor_messages__msg__Health__rosidl_typesupport_introspection_c__Health_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Float32)();
  motor_messages__msg__Health__rosidl_typesupport_introspection_c__Health_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Float32)();
  motor_messages__msg__Health__rosidl_typesupport_introspection_c__Health_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Float32)();
  motor_messages__msg__Health__rosidl_typesupport_introspection_c__Health_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Bool)();
  if (!motor_messages__msg__Health__rosidl_typesupport_introspection_c__Health_message_type_support_handle.typesupport_identifier) {
    motor_messages__msg__Health__rosidl_typesupport_introspection_c__Health_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &motor_messages__msg__Health__rosidl_typesupport_introspection_c__Health_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
