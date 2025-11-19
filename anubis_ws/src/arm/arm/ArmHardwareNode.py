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
            "/cmd_joint_pos",
            self.listener_callback,
            10)
      self.subscription_  # prevent unused variable warning
      joint_states_deg = [90, 45, 180, 0, 90]
      self.joint_states = [math.radians(deg) for deg in joint_states_deg]
      self.arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)
      self.joint_state_pub = self.create_publisher(JointState, '/joint_states', 10)
      self.feedback_timer = self.create_timer(0.05, self.feedback_callback)
      self.moving = False

   def listener_callback(self, msg):
      print('Listens')
      self.get_logger().info('I heard: "%s"' % msg.data)
      serial_message = ''
      for position in msg.data:
         serial_message += str(int(position * 180/ math.pi)) + ","
      print(serial_message)
      if list(msg.data) != list(self.joint_states):
         self.arduino.write(bytes(serial_message, 'utf-8'))
      data = self.arduino.readline()
      print("FROM ARDUINO\n")
      print(data)
      self.joint_states = msg.data

   def feedback_callback(self):
      js = JointState()
      js.header.stamp = self.get_clock().now().to_msg()
      js.name.append("base_joint")
      js.name.append("shoulder_joint")
      js.name.append("elbow_joint")
      js.name.append("wrist_pitch_joint")
      js.name.append("wrist_roll_joint")
      # js.name.append("gripper_joint")
      # js.name.append("braccio_virtual_joint")
      # js.name.append("gripper_joint")
      positions_rad = []
      positions_degree = []
      for p in self.joint_states:
         rad = float(p)
         positions_rad.append(rad)
         # positions_degree.append(float(p))
      # if self.moving:
      #    positions_degree[3] = 100
      # js.position = positions_degree
      js.position = positions_rad
      time.sleep(0.05)
      self.joint_state_pub.publish(js)
      # print(js.name)
      # print(js.position)
      # self.moving = not self.moving



def main(args=None):
   rclpy.init(args=args)

   minimal_subscriber = ArmHardware()

   rclpy.spin(minimal_subscriber)

   minimal_subscriber.destroy_node()
   rclpy.shutdown()
   #


if __name__ == '__main__':
   main()