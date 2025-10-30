import rclpy
import serial
from std_msgs.msg import Float64MultiArray
from rclpy.node import Node

from std_msgs.msg import String


class ArmHardware(Node):

   def __init__(self):
      super().__init__('listener')
      self.subscription_ = self.create_subscription(
            Float64MultiArray,
            "/joint_pos"
            self.listener_callback,
            10)
      self.subscription_  # prevent unused variable warning
      self.arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1) 
      
   def listener_callback(self, msg):
      self.get_logger().info('I heard: "%s"' % msg.data)
      serial_message = ""
      for position in msg.data:
         serial_message += str(position) + ","
      self.arduino.write(bytes(serial_message, 'utf-8')) 


def main(args=None):
   rclpy.init(args=args)

   minimal_subscriber = ArmHardware()

   rclpy.spin(minimal_subscriber)

   minimal_subscriber.destroy_node()
   rclpy.shutdown()


if __name__ == '__main__':
   main()