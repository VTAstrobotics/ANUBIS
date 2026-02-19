#include <memory>
#include <chrono>
#include <vector>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "motor_messages/msg/command.hpp"
#include "motor_control/kraken_controller.hpp"
#include "motor_control/motor_controller_base.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

#define MAX_MOTORS 4

#define RADIAN_TO_REV 0.15915494

#define BASE_LAT_GR 1
#define BASE_JOINT_GR 125
#define ELBOW_JOINT_GR 108
#define END_EFFECTOR_GR 45
float GEAR_RATIOS[4] = {BASE_LAT_GR, BASE_JOINT_GR, ELBOW_JOINT_GR, END_EFFECTOR_GR};

enum JOINT
{
  BASE_LAT = 0,
  BASE_JOINT,
  ELBOW,
  END_EFFECTOR
};

struct joint_motor_publishers
{
  rclcpp::Publisher<motor_messages::msg::Command>::SharedPtr left_publisher;
  rclcpp::Publisher<motor_messages::msg::Command>::SharedPtr right_publisher;
};

using std::placeholders::_1;
class ArmHardwareNode : public rclcpp::Node

{
public:
  ArmHardwareNode()
      : Node("arm_hardware_node") // name of the node
  {
    init_joint_motor_publishers();
    joint_pos_subscriber = this->create_subscription<std_msgs::msg::Float64MultiArray>(
        "/joint_positions_radians", 10, std::bind(&ArmHardwareNode::joint_pos_callback, this, _1));
  }

private:
  joint_motor_publishers motor_publishers[MAX_MOTORS]; // 5 DOF, 2 motors each

  float prev_angles[MAX_MOTORS] = {0}; // assume all zeroes, can change this to init position

  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr joint_pos_subscriber;

  motor_messages::msg::Command motor_msgs[MAX_MOTORS];


  void init_joint_motor_publishers()
  {
    motor_publishers[BASE_LAT].left_publisher = this->create_publisher<motor_messages::msg::Command>("/base_lat_left/control", 10);
    motor_publishers[BASE_LAT].right_publisher = this->create_publisher<motor_messages::msg::Command>("/base_lat_right/control", 10);

    motor_publishers[BASE_JOINT].left_publisher = this->create_publisher<motor_messages::msg::Command>("/base_joint_left/control", 10);
    motor_publishers[BASE_JOINT].right_publisher = this->create_publisher<motor_messages::msg::Command>("/base_joint_right/control", 10);

    motor_publishers[ELBOW].left_publisher = this->create_publisher<motor_messages::msg::Command>("/elbow_left/control", 10);
    motor_publishers[ELBOW].right_publisher = this->create_publisher<motor_messages::msg::Command>("/elbow_right/control", 10);

    motor_publishers[END_EFFECTOR].left_publisher = this->create_publisher<motor_messages::msg::Command>("/end_effector_left/control", 10);
    motor_publishers[END_EFFECTOR].right_publisher = this->create_publisher<motor_messages::msg::Command>("/end_effector_right/control", 10);
  }

  void joint_pos_callback(std_msgs::msg::Float64MultiArray::SharedPtr msg)
  {

    float sent_angles[MAX_MOTORS];

    for (int i = 0; i < MAX_MOTORS; i++)
    {
      sent_angles[i] = msg->data[i];
    }
    float rotations[MAX_MOTORS];

    angles_to_rotations(sent_angles, prev_angles, rotations);
    publish_rotations(rotations);

    for (int i = 0; i < MAX_MOTORS; i++)
    {
      prev_angles[i] = sent_angles[i]; // TODO: fake feedback for now.
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
    for (int i = 0; i < MAX_MOTORS; i++)
    {
      motor_msgs[i].position.data = array[i];
      motor_publishers[i].left_publisher->publish(motor_msgs[i]);
      motor_publishers[i].right_publisher->publish(motor_msgs[i]);
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