// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from motor_messages:msg/Health.idl
// generated code does not contain a copyright notice
#include "motor_messages/msg/detail/health__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `voltage`
// Member `temperature`
// Member `current`
#include "std_msgs/msg/detail/float32__functions.h"
// Member `is_failed`
#include "std_msgs/msg/detail/bool__functions.h"

bool
motor_messages__msg__Health__init(motor_messages__msg__Health * msg)
{
  if (!msg) {
    return false;
  }
  // voltage
  if (!std_msgs__msg__Float32__init(&msg->voltage)) {
    motor_messages__msg__Health__fini(msg);
    return false;
  }
  // temperature
  if (!std_msgs__msg__Float32__init(&msg->temperature)) {
    motor_messages__msg__Health__fini(msg);
    return false;
  }
  // current
  if (!std_msgs__msg__Float32__init(&msg->current)) {
    motor_messages__msg__Health__fini(msg);
    return false;
  }
  // is_failed
  if (!std_msgs__msg__Bool__init(&msg->is_failed)) {
    motor_messages__msg__Health__fini(msg);
    return false;
  }
  return true;
}

void
motor_messages__msg__Health__fini(motor_messages__msg__Health * msg)
{
  if (!msg) {
    return;
  }
  // voltage
  std_msgs__msg__Float32__fini(&msg->voltage);
  // temperature
  std_msgs__msg__Float32__fini(&msg->temperature);
  // current
  std_msgs__msg__Float32__fini(&msg->current);
  // is_failed
  std_msgs__msg__Bool__fini(&msg->is_failed);
}

bool
motor_messages__msg__Health__are_equal(const motor_messages__msg__Health * lhs, const motor_messages__msg__Health * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // voltage
  if (!std_msgs__msg__Float32__are_equal(
      &(lhs->voltage), &(rhs->voltage)))
  {
    return false;
  }
  // temperature
  if (!std_msgs__msg__Float32__are_equal(
      &(lhs->temperature), &(rhs->temperature)))
  {
    return false;
  }
  // current
  if (!std_msgs__msg__Float32__are_equal(
      &(lhs->current), &(rhs->current)))
  {
    return false;
  }
  // is_failed
  if (!std_msgs__msg__Bool__are_equal(
      &(lhs->is_failed), &(rhs->is_failed)))
  {
    return false;
  }
  return true;
}

bool
motor_messages__msg__Health__copy(
  const motor_messages__msg__Health * input,
  motor_messages__msg__Health * output)
{
  if (!input || !output) {
    return false;
  }
  // voltage
  if (!std_msgs__msg__Float32__copy(
      &(input->voltage), &(output->voltage)))
  {
    return false;
  }
  // temperature
  if (!std_msgs__msg__Float32__copy(
      &(input->temperature), &(output->temperature)))
  {
    return false;
  }
  // current
  if (!std_msgs__msg__Float32__copy(
      &(input->current), &(output->current)))
  {
    return false;
  }
  // is_failed
  if (!std_msgs__msg__Bool__copy(
      &(input->is_failed), &(output->is_failed)))
  {
    return false;
  }
  return true;
}

motor_messages__msg__Health *
motor_messages__msg__Health__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_messages__msg__Health * msg = (motor_messages__msg__Health *)allocator.allocate(sizeof(motor_messages__msg__Health), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(motor_messages__msg__Health));
  bool success = motor_messages__msg__Health__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
motor_messages__msg__Health__destroy(motor_messages__msg__Health * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    motor_messages__msg__Health__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
motor_messages__msg__Health__Sequence__init(motor_messages__msg__Health__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_messages__msg__Health * data = NULL;

  if (size) {
    data = (motor_messages__msg__Health *)allocator.zero_allocate(size, sizeof(motor_messages__msg__Health), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = motor_messages__msg__Health__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        motor_messages__msg__Health__fini(&data[i - 1]);
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
motor_messages__msg__Health__Sequence__fini(motor_messages__msg__Health__Sequence * array)
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
      motor_messages__msg__Health__fini(&array->data[i]);
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

motor_messages__msg__Health__Sequence *
motor_messages__msg__Health__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  motor_messages__msg__Health__Sequence * array = (motor_messages__msg__Health__Sequence *)allocator.allocate(sizeof(motor_messages__msg__Health__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = motor_messages__msg__Health__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
motor_messages__msg__Health__Sequence__destroy(motor_messages__msg__Health__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    motor_messages__msg__Health__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
motor_messages__msg__Health__Sequence__are_equal(const motor_messages__msg__Health__Sequence * lhs, const motor_messages__msg__Health__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!motor_messages__msg__Health__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
motor_messages__msg__Health__Sequence__copy(
  const motor_messages__msg__Health__Sequence * input,
  motor_messages__msg__Health__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(motor_messages__msg__Health);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    motor_messages__msg__Health * data =
      (motor_messages__msg__Health *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!motor_messages__msg__Health__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          motor_messages__msg__Health__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!motor_messages__msg__Health__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
