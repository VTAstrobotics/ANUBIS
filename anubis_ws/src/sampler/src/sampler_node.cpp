#include "rclcpp/rclcpp.hpp"
#include "motor_messages/msg/command.hpp"
#include "motor_control/sparkmax_controller.hpp"
#include "motor_control/motor_controller_base.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float32.hpp"
#include "motor.hpp"
    using std::placeholders::_1;

class Sampler : public rclcpp::Node{

    public: Sampler() : Node("drive_mode"){

        this->declare_parameter<std::string>("auger_motor", "auger");
        this->declare_parameter<std::string>("carousel_motor", "carousel");
        

        std::string auger = this->get_parameter("auger_motor").as_string();
        std::string carousel = this->get_parameter("carousel_motor").as_string();
        this->auger_motor = new motor(auger , this);
        this->carousel_motor = new motor(carousel, this);

        
        this->auger_control_subscriber = this->create_subscription<std_msgs::msg::Float32>(
        "/auger/command_speed", 10, std::bind(&Sampler::auger_callback, this, _1));
        this->carousel_motor_subscriber = this->create_subscription<std_msgs::msg::Float32>(
        "/carousel/command_speed", 10, std::bind(&Sampler::carousel_callback, this, _1));

    }


    void auger_callback(std_msgs::msg::Float32::SharedPtr msg){
        auger_command.dutycycle.data = msg->data;
        auger_motor->send_command(auger_command);
    }
    
    void carousel_callback(std_msgs::msg::Float32::SharedPtr msg){
        carousel_command.position.data += msg->data;
        carousel_motor->send_command(carousel_command);
    }

    private:
    motor* auger_motor;
    motor* carousel_motor;
    motor_messages::msg::Command auger_command;
    motor_messages::msg::Command carousel_command;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr auger_control_subscriber;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr carousel_motor_subscriber;

    
    

  
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Sampler>());
  rclcpp::shutdown();
  return 0;
}