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
#include "sensor_msgs/msg/joy.hpp"

#include "motor.hpp"
#include <cmath>

#define INIT_X M_PI
#define INIT_Y M_PI

#define a1 0.58
#define a2 0.58

#define AXIS_LINEAR 1
#define AXIS_ANGULAR 3

#define SCALE_CONSTANT 1




struct joint_angles_t
{
    float q1;
    float q2;
};

struct cartesian_position_t{
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
        cartesian_position.x = INIT_X;
        cartesian_position.y = INIT_Y;

    }

private:
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_subscriber;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr joint_angle_publisher;
    cartesian_position_t cartesian_position;    


    float compute_theta_2(float x, float y)
    {
        return std::acos(pow(x, 2) + pow(y, 2) - pow(a1, 2) - pow(a2, 2)) / (2 * a1 * a2);
    }

    float compute_theta_1(float x, float y, float q2)
    {
        return std::atan(y / x) - std::atan(((a2)*sin(q2)) / (a1 + a2 * cos(q2)));
    }

    joint_angles_t compute_angles(float x, float y)
    {
        joint_angles_t angles;
        angles.q2 = compute_theta_2(x, y);
        angles.q1 = compute_theta_1(x, y, angles.q2);
        return angles;
    }

    void joy_callback(sensor_msgs::msg::Joy::SharedPtr msg){
        float l_y =  msg->axes[AXIS_LINEAR];
        float l_x = msg->axes[AXIS_ANGULAR];

        float dx = cartesian_position.x + (l_y * SCALE_CONSTANT);
        float dy = cartesian_position.y + (l_x * SCALE_CONSTANT);

        dx = (std::abs(dx) > 0.01) ? (0.01 * signum(dx)) : dx;
        dx = (std::abs(dx) > 0.01) ? 0.01 * signum(dy) : dx;


        joint_angles_t joint_angles = compute_angles(dx, dy);

    }

    float signum(float x) { 
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