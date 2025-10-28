// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from motor_messages:msg/Feedback.idl
// generated code does not contain a copyright notice

#include "motor_messages/msg/detail/feedback__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_motor_messages
const rosidl_type_hash_t *
motor_messages__msg__Feedback__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x74, 0xfb, 0x38, 0x55, 0xe0, 0x7a, 0x65, 0x0b,
      0x80, 0x36, 0xe0, 0x44, 0x93, 0x19, 0x34, 0x2e,
      0xe5, 0x97, 0x51, 0x76, 0xb1, 0xb9, 0xe3, 0x8b,
      0xc9, 0x81, 0x0b, 0x81, 0xa6, 0x08, 0x06, 0x63,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "std_msgs/msg/detail/bool__functions.h"
#include "std_msgs/msg/detail/float32__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t std_msgs__msg__Bool__EXPECTED_HASH = {1, {
    0xfe, 0xb9, 0x1e, 0x99, 0x5f, 0xf9, 0xeb, 0xd0,
    0x9c, 0x0c, 0xb3, 0xd2, 0xae, 0xd1, 0x8b, 0x11,
    0x07, 0x75, 0x85, 0x83, 0x9f, 0xb5, 0xdb, 0x80,
    0x19, 0x3b, 0x62, 0xd7, 0x45, 0x28, 0xf6, 0xc9,
  }};
static const rosidl_type_hash_t std_msgs__msg__Float32__EXPECTED_HASH = {1, {
    0x71, 0x70, 0xd3, 0xd8, 0xf8, 0x41, 0xf7, 0xbe,
    0x31, 0x72, 0xce, 0x5f, 0x4f, 0x59, 0xf3, 0xa4,
    0xd7, 0xf6, 0x3b, 0x04, 0x47, 0xe8, 0xb3, 0x33,
    0x27, 0x60, 0x1a, 0xd6, 0x4d, 0x83, 0xd6, 0xe2,
  }};
#endif

static char motor_messages__msg__Feedback__TYPE_NAME[] = "motor_messages/msg/Feedback";
static char std_msgs__msg__Bool__TYPE_NAME[] = "std_msgs/msg/Bool";
static char std_msgs__msg__Float32__TYPE_NAME[] = "std_msgs/msg/Float32";

// Define type names, field names, and default values
static char motor_messages__msg__Feedback__FIELD_NAME__velocity[] = "velocity";
static char motor_messages__msg__Feedback__FIELD_NAME__current[] = "current";
static char motor_messages__msg__Feedback__FIELD_NAME__position[] = "position";
static char motor_messages__msg__Feedback__FIELD_NAME__is_disabled[] = "is_disabled";

static rosidl_runtime_c__type_description__Field motor_messages__msg__Feedback__FIELDS[] = {
  {
    {motor_messages__msg__Feedback__FIELD_NAME__velocity, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Float32__TYPE_NAME, 20, 20},
    },
    {NULL, 0, 0},
  },
  {
    {motor_messages__msg__Feedback__FIELD_NAME__current, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Float32__TYPE_NAME, 20, 20},
    },
    {NULL, 0, 0},
  },
  {
    {motor_messages__msg__Feedback__FIELD_NAME__position, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Float32__TYPE_NAME, 20, 20},
    },
    {NULL, 0, 0},
  },
  {
    {motor_messages__msg__Feedback__FIELD_NAME__is_disabled, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Bool__TYPE_NAME, 17, 17},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription motor_messages__msg__Feedback__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {std_msgs__msg__Bool__TYPE_NAME, 17, 17},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Float32__TYPE_NAME, 20, 20},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
motor_messages__msg__Feedback__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {motor_messages__msg__Feedback__TYPE_NAME, 27, 27},
      {motor_messages__msg__Feedback__FIELDS, 4, 4},
    },
    {motor_messages__msg__Feedback__REFERENCED_TYPE_DESCRIPTIONS, 2, 2},
  };
  if (!constructed) {
    assert(0 == memcmp(&std_msgs__msg__Bool__EXPECTED_HASH, std_msgs__msg__Bool__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = std_msgs__msg__Bool__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Float32__EXPECTED_HASH, std_msgs__msg__Float32__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = std_msgs__msg__Float32__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "std_msgs/Float32 velocity\n"
  "std_msgs/Float32 current\n"
  "std_msgs/Float32 position\n"
  "std_msgs/Bool is_disabled";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
motor_messages__msg__Feedback__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {motor_messages__msg__Feedback__TYPE_NAME, 27, 27},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 103, 103},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
motor_messages__msg__Feedback__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[3];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 3, 3};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *motor_messages__msg__Feedback__get_individual_type_description_source(NULL),
    sources[1] = *std_msgs__msg__Bool__get_individual_type_description_source(NULL);
    sources[2] = *std_msgs__msg__Float32__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
