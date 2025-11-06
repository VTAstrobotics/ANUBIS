import rclpy
import serial
from std_msgs.msg import Float64MultiArray
from rclpy.node import Node
import time
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
      self.arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)
      self.joint_pos_publisher = self.create_publisher(JointState, '/joint_states', 10)

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
      js = JointState()
      js.header.stamp = self.get_clock().now().to_msg()
      js.name[0] = "joint0"
      js.name[1] = "joint1"
      js.name[2] = "joint2"
      js.name[3] = "joint3"
      js.name[4] = "joint4"
      js.name[5] = "joint5"
      positions_rad = []
      for p in msg.data:
         deg = float(p)
         rad = deg * math.pi / 180.0
         positions_rad.append(rad)

      js.position = positions_rad

      self.joint_state_pub.publish(js)



def main(args=None):
   rclpy.init(args=args)

   minimal_subscriber = ArmHardware()

   rclpy.spin(minimal_subscriber)

   minimal_subscriber.destroy_node()
   rclpy.shutdown()


if __name__ == '__main__':
   main()