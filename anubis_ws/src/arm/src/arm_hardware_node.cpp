#include <memory>
#include <chrono>
#include <vector>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "motor_messages/msg/command.hpp"
#include "motor_messages/msg/feedback.hpp"
#include "motor_control/kraken_controller.hpp"
#include "motor_control/motor_controller_base.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

#include "motor.hpp"
#include "encoder.hpp"

#define MAX_MOTORS 4

#define RADIAN_TO_REV 0.15915494

#define BASE_LAT_GR 1
#define BASE_JOINT_GR 125
#define ELBOW_GR 108
#define END_EFFECTOR_GR 45
float GEAR_RATIOS[4] = {BASE_LAT_GR, BASE_JOINT_GR, ELBOW_GR, END_EFFECTOR_GR};

#define BASE_JOINT_CANCODER_ID 0 // Both need to be set to real CAN IDs
#define ELBOW_CANCODER_ID 0 // Should probably live in a different file but its here for now

enum JOINT
{
  BASE_LAT = 0,
  BASE_JOINT,
  ELBOW,
  END_EFFECTOR
};
struct joint_motors
{
  std::shared_ptr<motor> left_motor;
  std::shared_ptr<motor> right_motor;
  std::shared_ptr<encoder> cancoder;
};

using std::placeholders::_1;
class ArmHardwareNode : public rclcpp::Node

{
public:
  ArmHardwareNode()
      : Node("arm_hardware_node") // name of the node
  {
    init_motor_array();
    joint_pos_subscriber = this->create_subscription<std_msgs::msg::Float64MultiArray>(
        "/joint_positions_radians", 10, std::bind(&ArmHardwareNode::joint_pos_callback, this, _1));
  }

private:
  float prev_angles[MAX_MOTORS] = {0}; // assume all zeroes, can change this to init position

  float prev_angles_test[MAX_MOTORS] = {0};

  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr joint_pos_subscriber;

  motor_messages::msg::Command motor_msgs[MAX_MOTORS];

  joint_motors joint[MAX_MOTORS];

  void init_motor_array()
  {
    joint[BASE_LAT].left_motor = std::make_shared<motor>("base_lat_left", this);
    joint[BASE_LAT].right_motor = std::make_shared<motor>("base_lat_right", this);
    //No CANCoder as far as I know

    joint[BASE_JOINT].left_motor = std::make_shared<motor>("base_joint_left", this);
    joint[BASE_JOINT].right_motor = std::make_shared<motor>("base_joint_right", this);
    joint[BASE_JOINT].cancoder = std::make_shared<encoder>("can1", BASE_JOINT_CANCODER_ID, true);

    joint[ELBOW].left_motor = std::make_shared<motor>("elbow_left", this);
    joint[ELBOW].right_motor = std::make_shared<motor>("elbow_right", this);
    joint[ELBOW].cancoder = std::make_shared<encoder>("can1", ELBOW_CANCODER_ID, true);

    joint[END_EFFECTOR].left_motor = std::make_shared<motor>("end_effector_left", this);
    joint[END_EFFECTOR].right_motor = std::make_shared<motor>("end_effector_right", this);
    //No CANCoder as far as I know
  }

  void joint_pos_callback(std_msgs::msg::Float64MultiArray::SharedPtr msg)
  {

    float sent_angles[MAX_MOTORS];

    for (int i = 0; i < MAX_MOTORS; i++)
    {
      sent_angles[i] = msg->data[i];
    }
    float rotations[MAX_MOTORS];

    update_prev_angles();
    // angles_to_rotations(sent_angles, prev_angles, rotations);
    angles_to_rotations(sent_angles, prev_angles_test, rotations);
    publish_rotations(rotations);
    motor_msgs[0].dutycycle.data = msg->data[0];
    joint[0].right_motor->send_command(motor_msgs[0]);
    joint[0].left_motor->send_command(motor_msgs[0]);

    for (int i = 0; i < MAX_MOTORS; i++)
    {
      prev_angles[i] = sent_angles[i]; // TODO: fake feedback for now. can replace with prev_angles_test
    }
  }

  void update_prev_angles()
  {
    for (int i = 0; i < MAX_MOTORS; i++)
    {
      prev_angles_test[i] = ((static_cast<float>(joint[i].left_motor->get_motor_state().position.data) +
                              static_cast<float>(joint[i].right_motor->get_motor_state().position.data)) /
                             2.0) *
                            (2 * M_PI) / GEAR_RATIOS[i]; // lets average for now
    }
  }

  void angles_to_rotations(float *current_angles, float *previous_angles, float *output)
  {
    for (int i = 0; i < MAX_MOTORS; i++)
    {
      output[i] = (current_angles[i] - previous_angles[i]) * GEAR_RATIOS[i] / (2 * M_PI);
    }
  }

  void publish_rotations(float *array)
  {
    for (int i = 1; i < MAX_MOTORS; i++)
    {
      motor_msgs[i].position.data = array[i];
      joint[i].left_motor->send_command(motor_msgs[i]);
      joint[i].right_motor->send_command(motor_msgs[i]);
    }
  }
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ArmHardwareNode>());
  rclcpp::shutdown();
  return 0;
}