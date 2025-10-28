// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motor_messages:msg/Feedback.idl
// generated code does not contain a copyright notice
#include "motor_messages/msg/detail/feedback__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `velocity`
// Member `current`
// Member `position`
#include "std_msgs/msg/detail/float32__functions.h"
// Member `is_disabled`
#include "std_msgs/msg/detail/bool__functions.h"

bool
motor_messages__msg__Feedback__init(motor_messages__msg__Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // velocity
  if (!std_msgs__msg__Float32__init(&msg->velocity)) {
    motor_messages__msg__Feedback__fini(msg);
    return false;
  }
  // current
  if (!std_msgs__msg__Float32__init(&msg->current)) {
    motor_messages__msg__Feedback__fini(msg);
    return false;
  }
  // position
  if (!std_msgs__msg__Float32__init(&msg->position)) {
    motor_messages__msg__Feedback__fini(msg);
    return false;
  }
  // is_disabled
  if (!std_msgs__msg__Bool__init(&msg->is_disabled)) {
    motor_messages__msg__Feedback__fini(msg);
    return false;
  }
  return true;
}

void
motor_messages__msg__Feedback__fini(motor_messages__msg__Feedback * msg)
{
  if (!msg) {
    return;
  }
  // velocity
  std_msgs__msg__Float32__fini(&msg->velocity);
  // current
  std_msgs__msg__Float32__fini(&msg->current);
  // position
  std_msgs__msg__Float32__fini(&msg->position);
  // is_disabled
  std_msgs__msg__Bool__fini(&msg->is_disabled);
}

bool
motor_messages__msg__Feedback__are_equal(const motor_messages__msg__Feedback * lhs, const motor_messages__msg__Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // velocity
  if (!std_msgs__msg__Float32__are_equal(
      &(lhs->velocity), &(rhs->velocity)))
  {
    return false;
  }
  // current
  if (!std_msgs__msg__Float32__are_equal(
      &(lhs->current), &(rhs->current)))
  {
    return false;
  }
  // position
  if (!std_msgs__msg__Float32__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  // is_disabled
  if (!std_msgs__msg__Bool__are_equal(
      &(lhs->is_disabled), &(rhs->is_disabled)))
  {
    return false;
  }
  return true;
}

bool
motor_messages__msg__Feedback__copy(
  const motor_messages__msg__Feedback * input,
  motor_messages__msg__Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // velocity
  if (!std_msgs__msg__Float32__copy(
      &(input->velocity), &(output->velocity)))
  {
    return false;
  }
  // current
  if (!std_msgs__msg__Float32__copy(
      &(input->current), &(output->current)))
  {
    return false;
  }
  // position
  if (!std_msgs__msg__Float32__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  // is_disabled
  if (!std_msgs__msg__Bool__copy(
      &(input->is_disabled), &(output->is_disabled)))
  {
    return false;
  }
  return true;
}

motor_messages__msg__Feedback *
motor_messages__msg__Feedback__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_messages__msg__Feedback * msg = (motor_messages__msg__Feedback *)allocator.allocate(sizeof(motor_messages__msg__Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motor_messages__msg__Feedback));
  bool success = motor_messages__msg__Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motor_messages__msg__Feedback__destroy(motor_messages__msg__Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motor_messages__msg__Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motor_messages__msg__Feedback__Sequence__init(motor_messages__msg__Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_messages__msg__Feedback * data = NULL;

  if (size) {
    data = (motor_messages__msg__Feedback *)allocator.zero_allocate(size, sizeof(motor_messages__msg__Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motor_messages__msg__Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motor_messages__msg__Feedback__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
motor_messages__msg__Feedback__Sequence__fini(motor_messages__msg__Feedback__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      motor_messages__msg__Feedback__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

motor_messages__msg__Feedback__Sequence *
motor_messages__msg__Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_messages__msg__Feedback__Sequence * array = (motor_messages__msg__Feedback__Sequence *)allocator.allocate(sizeof(motor_messages__msg__Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motor_messages__msg__Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motor_messages__msg__Feedback__Sequence__destroy(motor_messages__msg__Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motor_messages__msg__Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motor_messages__msg__Feedback__Sequence__are_equal(const motor_messages__msg__Feedback__Sequence * lhs, const motor_messages__msg__Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motor_messages__msg__Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motor_messages__msg__Feedback__Sequence__copy(
  const motor_messages__msg__Feedback__Sequence * input,
  motor_messages__msg__Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motor_messages__msg__Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motor_messages__msg__Feedback * data =
      (motor_messages__msg__Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motor_messages__msg__Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motor_messages__msg__Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motor_messages__msg__Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
