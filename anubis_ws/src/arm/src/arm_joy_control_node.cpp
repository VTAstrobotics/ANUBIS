#include <memory>
#include <chrono>
#include <vector>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "sensor_msgs/msg/joy.hpp"

#include <cmath>

#define a1 0.58
#define a2 0.58

#define INIT_X 0.5
#define INIT_Y 0.5

#define AXIS_LINEAR 1
#define AXIS_ANGULAR 3

#define JOY_FREQUENCY 50.0

#define SCALE_CONSTANT 0.01 / JOY_FREQUENCY

struct joint_angles_t
{
    float q1;
    float q2;
};

struct cartesian_position_t
{
    float x;
    float y;
};

using std::placeholders::_1;
class ArmJoyControl : public rclcpp::Node
{
public:
    ArmJoyControl()
        : Node("arm_joy_control_node") // name of the node
    {

        joy_subscriber = this->create_subscription<sensor_msgs::msg::Joy>(
            "/joy", 10, std::bind(&ArmJoyControl::joy_callback, this, _1));

        joint_angle_publisher = this->create_publisher<std_msgs::msg::Float32MultiArray>("/joint_positions_radians", 10);
        cartesian_position.x = INIT_X;
        cartesian_position.y = INIT_Y;

        RCLCPP_INFO(this->get_logger(), "Arm Joystick Control Started");

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
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_subscriber;
    rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr joint_angle_publisher;
    cartesian_position_t cartesian_position;

    float compute_theta_2(float x, float y)
    {
        float arccos_number = (pow(x, 2) + pow(y, 2) - pow(a1, 2) - pow(a2, 2)) / (2 * a1 * a2); // could comparing positive and negative results
        arccos_number = std::clamp(arccos_number, -1.0f, 1.0f);

        float theta_2 = std::acos(arccos_number);

        if (std::isnan(theta_2))
        {
            RCLCPP_ERROR(this->get_logger(), "Pose out of bounds: Q1 nan");
        }

        return theta_2;
    }

    float compute_theta_1(float x, float y, float q2)
    {
        float theta_1 = std::atan2(y, x) - std::atan(((a2)*sin(q2)) / (a1 + a2 * cos(q2)));

        if (std::isnan(theta_1))
        {
            RCLCPP_ERROR(this->get_logger(), "Pose out of bounds: Q2 nan");
        }

        return theta_1;
    }

    joint_angles_t compute_angles(float x, float y)
    {
        joint_angles_t angles;
        angles.q2 = compute_theta_2(x, y);
        angles.q1 = compute_theta_1(x, y, angles.q2);
        return angles;
    }

    void joy_callback(sensor_msgs::msg::Joy::SharedPtr msg)
    {
        float l_y = (std::abs(msg->axes[1]) > 0.05) ? msg->axes[1] : 0;
        float l_x = (std::abs(msg->axes[0]) > 0.05) ? msg->axes[0] : 0;
        float base_duty = (std::abs(msg->axes[3]) > 0.05) ? msg->axes[3] : 0;

        float dx = (l_x * SCALE_CONSTANT * 1.0);
        float dy = (l_y * SCALE_CONSTANT * 1.0);

        if (!(pow(cartesian_position.x + dx, 2) + pow(cartesian_position.y + dy, 2) > pow((a1 + a2), 2))) // need to check for inner bound as well
        {
            cartesian_position.x += dx;
            cartesian_position.y += dy;
        }

        joint_angles_t joint_angles = compute_angles(cartesian_position.x, cartesian_position.y);

        auto message = std_msgs::msg::Float32MultiArray();
        std::vector<float> positions = {base_duty, joint_angles.q1, joint_angles.q2, 0};
        message.data = positions;
        joint_angle_publisher->publish(message);
    }

    float signum(float x)
    {
        return (x > 0) - (x < 0);
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ArmJoyControl>());
    rclcpp::shutdown();
    return 0;
}
