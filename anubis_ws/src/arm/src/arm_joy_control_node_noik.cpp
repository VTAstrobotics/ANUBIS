#include <memory>
#include <chrono>
#include <vector>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "motor.hpp"
#include "encoder.hpp"
#include "motor_messages/msg/command.hpp"

#include <iostream>

#include <cmath>

#define AXIS_LINEAR 1
#define AXIS_ANGULAR 3
#define JOINT_SWITCH 5
#define EE_CLOSE 2
#define EE_OPEN 1
#define JOINTS 4

enum JOINT
{
    BASE_LAT = 0,
    BASE_JOINT,
    ELBOW,
    END_EFFECTOR
};

struct joint_motors_t
{
    std::shared_ptr<motor> left_motor;
    std::shared_ptr<motor> right_motor;
    std::shared_ptr<encoder> cancoder;
};

using std::placeholders::_1;
class ArmJoyControlNoIK : public rclcpp::Node
{
public:
    ArmJoyControlNoIK()
        : Node("arm_joy_control_node_noik") // name of the node
    {
        joy_subscriber = this->create_subscription<sensor_msgs::msg::Joy>(
            "/joy", 10, std::bind(&ArmJoyControlNoIK::joy_callback, this, _1));
        init_joint_motors();

        std::cout
            << R"(
    
       _______
     _/       \_
    / |       | \
   /  |__   __|  \
  |__/((o| |o))\__|
  |      | |      |
  |\     |_|     /|
  | \           / |
   \| /  ___  \ |/
    \ | / _ \ | /
     \_________/
      _|_____|_
 ____|_________|____
/                   \  -- Mark Moi    
    )" << std::endl;
    }

private:
    joint_motors_t joint_motors[JOINTS];
    JOINT joint_control_state = BASE_LAT;
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_subscriber;
    bool prev_joint_switch_state = false;

    std::shared_ptr<motor> grabber = std::make_shared<motor>("grabber", this);

    void init_joint_motors()
    {
        joint_motors[BASE_LAT].left_motor = std::make_shared<motor>("base_lat_left", this);
        joint_motors[BASE_LAT].right_motor = std::make_shared<motor>("base_lat_right", this);

        joint_motors[BASE_JOINT].left_motor = std::make_shared<motor>("base_joint_left", this);
        joint_motors[BASE_JOINT].right_motor = std::make_shared<motor>("base_joint_right", this);
        joint_motors[BASE_JOINT].cancoder = std::make_shared<encoder>("can1", 50, true, 0.3);

        joint_motors[ELBOW].left_motor = std::make_shared<motor>("elbow_left", this);
        joint_motors[ELBOW].right_motor = std::make_shared<motor>("elbow_right", this);
        joint_motors[ELBOW].cancoder = std::make_shared<encoder>("can1", 51, true, 0.3); // replace with real canID

        joint_motors[END_EFFECTOR].left_motor = std::make_shared<motor>("end_effector_left", this);
        joint_motors[END_EFFECTOR].right_motor = std::make_shared<motor>("end_effector_right", this);
        // joint_motors[END_EFFECTOR].cancoder = std::make_shared<encoder>("can1", 52, true, 0.3);
    }

    void joy_callback(sensor_msgs::msg::Joy::SharedPtr msg)
    {
        motor_messages::msg::Command motor_msg_duty;

        if (msg->buttons[EE_CLOSE]) // gripper logic
        {
            motor_msg_duty.dutycycle.data = 1.0; // full speed ahead
            grabber->send_command(motor_msg_duty);
        }
        if (msg->buttons[EE_OPEN])
        {
            motor_msg_duty.dutycycle.data = -1.0;
            grabber->send_command(motor_msg_duty);
        }

        if (std::abs(msg->axes[AXIS_LINEAR]) < 0.01 && std::abs(msg->axes[AXIS_ANGULAR]) < 0.01)
        {
            motor_messages::msg::Command motor_msg_position;

            float angle1 = joint_motors[BASE_JOINT].cancoder->get_angle();
            motor_msg_position.position.data = angle1;
            joint_motors[BASE_JOINT].left_motor->send_command(motor_msg_position);
            joint_motors[BASE_JOINT].right_motor->send_command(motor_msg_position);

            float angle2 = joint_motors[ELBOW].cancoder->get_angle();
            motor_msg_position.position.data = angle2;
            joint_motors[ELBOW].left_motor->send_command(motor_msg_position);
            joint_motors[ELBOW].right_motor->send_command(motor_msg_position);
            RCLCPP_INFO(this->get_logger(), "HALTING ARM - angle 1: %f, angle 2: %f", angle1, angle2);
            return;
        }

        bool current_switch_state = false;
        current_switch_state = (msg->buttons[JOINT_SWITCH] == 1);

        if (current_switch_state && !prev_joint_switch_state)
        {
            joint_control_state =
                static_cast<JOINT>((joint_control_state + 1) % JOINTS);
            RCLCPP_INFO(this->get_logger(), "SWITCHED JOINT");
        }
        prev_joint_switch_state = current_switch_state;

        switch (joint_control_state)
        {
        case BASE_LAT:
            motor_msg_duty.dutycycle.data = msg->axes[AXIS_LINEAR] / 0.5; // scaled down
            joint_motors[BASE_LAT].left_motor->send_command(motor_msg_duty);
            joint_motors[BASE_LAT].right_motor->send_command(motor_msg_duty);
            break;
        case BASE_JOINT:
            motor_msg_duty.dutycycle.data = msg->axes[AXIS_LINEAR] / 0.5;
            joint_motors[BASE_JOINT].left_motor->send_command(motor_msg_duty);
            joint_motors[BASE_JOINT].right_motor->send_command(motor_msg_duty);
            break;
        case ELBOW:
            motor_msg_duty.dutycycle.data = msg->axes[AXIS_LINEAR] / 0.5;
            joint_motors[ELBOW].left_motor->send_command(motor_msg_duty);
            joint_motors[ELBOW].right_motor->send_command(motor_msg_duty);
            break;
        case END_EFFECTOR:
        {
            float lin = msg->axes[AXIS_LINEAR];
            float ang = msg->axes[AXIS_ANGULAR];

            double left_duty = ((lin - 0.5 * ang) / 1.5); // normalize
            motor_msg_duty.dutycycle.data = left_duty;
            joint_motors[END_EFFECTOR].left_motor->send_command(motor_msg_duty);

            double right_duty = ((lin + 0.5 * ang) / 1.5);
            motor_msg_duty.dutycycle.data = right_duty;
            joint_motors[END_EFFECTOR].right_motor->send_command(motor_msg_duty);
            break;
        }
        }
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ArmJoyControlNoIK>());
    rclcpp::shutdown();
    return 0;
}
