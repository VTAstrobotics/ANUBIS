import rclpy
import serial
from std_msgs.msg import Float64MultiArray
from rclpy.node import Node
import time
from std_msgs.msg import String


class ArmHardware(Node):

   def __init__(self):
      super().__init__('listener')
      self.subscription_ = self.create_subscription(
            Float64MultiArray,
            "/joint_pos",
            self.listener_callback,
            10)
      self.subscription_  # prevent unused variable warning
      self.arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)

   def listener_callback(self, msg):
      self.get_logger().info('I heard: "%s"' % msg.data)
      serial_message = ""
      for position in msg.data:
         serial_message += str(int(position)) + ","
      print(serial_message)
      self.arduino.write(bytes(serial_message, 'utf-8'))
      time.sleep(0.05)
      data = self.arduino.readline()
      print(data)



def main(args=None):
   rclpy.init(args=args)

   minimal_subscriber = ArmHardware()

   rclpy.spin(minimal_subscriber)

   minimal_subscriber.destroy_node()
   rclpy.shutdown()


if __name__ == '__main__':
   main()