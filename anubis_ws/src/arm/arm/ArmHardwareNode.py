import rclpy
import serial
from std_msgs.msg import Float64MultiArray
from rclpy.node import Node
import time
import math
from std_msgs.msg import String
from sensor_msgs.msg import JointState

class ArmHardware(Node):

   def __init__(self):
      super().__init__('listener')
      self.subscription_ = self.create_subscription(
            Float64MultiArray,
            "/joint_pos",
            self.listener_callback,
            10)
      self.subscription_  # prevent unused variable warning
      self.arduino = serial.Serial(port='/dev/ttyACM1', baudrate=9600, timeout=.1)
      self.joint_state_pub = self.create_publisher(JointState, '/joint_states', 10)

   def listener_callback(self, msg):
      print('Listens')
      self.get_logger().info('I heard: "%s"' % msg.data)
      serial_message = ''
      for position in msg.data:
         serial_message += str(int(position)) + ","
      print(serial_message)
      self.arduino.write(bytes(serial_message, 'utf-8'))
      time.sleep(0.05)
      data = self.arduino.readline()
      print(data)
      js = JointState()
      js.header.stamp = self.get_clock().now().to_msg()
      js.name.append("base_joint")
      js.name.append("shoulder_joint")
      js.name.append("elbow_joint")
      js.name.append("wrist_pitch_joint")
      js.name.append("wrist_roll_joint")
      js.name.append("gripper_joint")
      positions_rad = []
      positions_degree = []
      for p in msg.data:
         # deg = float(p)
         # rad = deg * math.pi / 180.0
         # positions_rad.append(rad)
         positions_degree.append(float(p))
      js.position = positions_degree
      time.sleep(0.05)
      self.joint_state_pub.publish(js)



def main(args=None):
   rclpy.init(args=args)

   minimal_subscriber = ArmHardware()

   rclpy.spin(minimal_subscriber)

   minimal_subscriber.destroy_node()
   rclpy.shutdown()
   #


if __name__ == '__main__':
   main()