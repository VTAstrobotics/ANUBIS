#include <memory>
#include <chrono>
#include <vector>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "motor.hpp"
#include "motor_messages/msg/command.hpp"

#include <iostream>

#include <cmath>

#define a1 0.58
#define a2 0.58

#define INIT_X 0.5
#define INIT_Y 0.5

#define AXIS_LINEAR 1
#define AXIS_ANGULAR 3

#define JOY_FREQUENCY 50.0

#define SCALE_CONSTANT 0.01 / JOY_FREQUENCY

#define JOINTS 4

#define JOINT_SWITCH 5

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
    // std::shared_ptr<encoder> cancoder;
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

        std::cout << R"(
    
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

    void init_joint_motors()
    {
        joint_motors[BASE_LAT].left_motor = std::make_shared<motor>("base_lat_left", this);
        joint_motors[BASE_LAT].right_motor = std::make_shared<motor>("base_lat_left", this);

        joint_motors[BASE_JOINT].left_motor = std::make_shared<motor>("base_joint_left", this);
        joint_motors[BASE_JOINT].right_motor = std::make_shared<motor>("base_joint_right", this);

        joint_motors[ELBOW].left_motor = std::make_shared<motor>("elbow_left", this);
        joint_motors[ELBOW].right_motor = std::make_shared<motor>("elbow_right", this);

        joint_motors[END_EFFECTOR].left_motor = std::make_shared<motor>("end_effector_left", this);
        joint_motors[END_EFFECTOR].right_motor = std::make_shared<motor>("end_effector_right", this);
    }

    void joy_callback(sensor_msgs::msg::Joy::SharedPtr msg)
    {
        motor_messages::msg::Command motor_msg;
        if (msg->buttons[JOINT_SWITCH] == 1)
        {
            joint_control_state = static_cast<JOINT>((joint_control_state + 1) % 4);
        }
        switch (joint_control_state)
        {
        case BASE_LAT:
            motor_msg.dutycycle.data = msg->axes[AXIS_LINEAR];
            joint_motors[BASE_LAT].left_motor->send_command(motor_msg);
            joint_motors[BASE_LAT].right_motor->send_command(motor_msg);
            break;
        case BASE_JOINT:
            motor_msg.dutycycle.data = msg->axes[AXIS_LINEAR];
            joint_motors[BASE_JOINT].left_motor->send_command(motor_msg);
            joint_motors[BASE_JOINT].right_motor->send_command(motor_msg);
            break;
        case ELBOW:
            motor_msg.dutycycle.data = msg->axes[AXIS_LINEAR];
            joint_motors[ELBOW].left_motor->send_command(motor_msg);
            joint_motors[ELBOW].right_motor->send_command(motor_msg);
            break;
        case END_EFFECTOR:

            float lin = msg->axes[AXIS_LINEAR];
            float ang = msg->axes[AXIS_ANGULAR];

            double left_duty = ((lin - 0.5 * ang) / 1.5);
            motor_msg.dutycycle.data = left_duty;
            joint_motors[END_EFFECTOR].left_motor->send_command(motor_msg);

            double right_duty = ((lin + 0.5 * ang) / 1.5);
            motor_msg.dutycycle.data = right_duty;
            joint_motors[END_EFFECTOR].right_motor->send_command(motor_msg);
            break;
        // default:
        //     RCLCPP_ERROR(this->get_logger(), "STATE OUT OF BOUNDS");
        //     break;
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
