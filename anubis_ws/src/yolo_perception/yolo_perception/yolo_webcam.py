import os
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from vision_msgs.msg import Detection2D, Detection2DArray, ObjectHypothesisWithPose
from cv_bridge import CvBridge
from ultralytics import YOLO
import cv2


class HammerDetectorNode(Node):
    def __init__(self):
        super().__init__("hammer_detector_node")

        self.declare_parameter("model_path", "/home/swara23/ANUBIS/anubis_ws/src/yolo_perception/yolo_perception/T10_Best.pt")
        self.declare_parameter("confidence_threshold", 0.50)
        self.declare_parameter("image_topic", "/camera/image_raw")
        self.declare_parameter("publish_annotated", True)

        model_path         = self.get_parameter("model_path").value
        self.conf          = self.get_parameter("confidence_threshold").value
        img_topic          = self.get_parameter("image_topic").value
        self.pub_annotated = self.get_parameter("publish_annotated").value

        if not os.path.exists(model_path):
            self.get_logger().error(f"Weights file not found: {model_path}")
            raise RuntimeError("Missing weights file")

        self.model  = YOLO(model_path)
        self.bridge = CvBridge()
        
        #made change
        self.sub_image      = self.create_subscription(Image, img_topic, self.image_callback, 10)
        self.pub_detections = self.create_publisher(Detection2DArray, "/hammer_detections", 10)

        if self.pub_annotated:
            self.pub_debug = self.create_publisher(Image, "/hammer_detections/debug_image", 10)

        self.get_logger().info(f"Loaded {model_path} | Listening on {img_topic}")

    def image_callback(self, msg: Image):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding="bgr8")
        except Exception as e:
            self.get_logger().error(f"cv_bridge error: {e}")
            return

        # Run local inference
        results = self.model(cv_image, conf=self.conf, verbose=False)[0]

        det_array        = Detection2DArray()
        det_array.header = msg.header

        for box in results.boxes:
            conf     = float(box.conf[0])
            class_id = int(box.cls[0])
            label    = self.model.names[class_id]

            # box.xywh gives center_x, center_y, w, h
            cx, cy, w, h = box.xywh[0].tolist()

            det = Detection2D()
            det.header = msg.header
            det.bbox.center.position.x = cx
            det.bbox.center.position.y = cy
            det.bbox.size_x = w
            det.bbox.size_y = h

            hyp = ObjectHypothesisWithPose()
            hyp.hypothesis.class_id = label
            hyp.hypothesis.score    = conf
            det.results.append(hyp)
            det_array.detections.append(det)

        self.pub_detections.publish(det_array)
        self.get_logger().info(f"Detected {len(det_array.detections)} object(s)")

        if self.pub_annotated:
            annotated = results.plot()  # ultralytics draws boxes for us
            try:
                dbg = self.bridge.cv2_to_imgmsg(annotated, encoding="bgr8")
                dbg.header = msg.header
                self.pub_debug.publish(dbg)
            except Exception as e:
                self.get_logger().error(f"Debug image error: {e}")


def main(args=None):
    rclpy.init(args=args)
    try:
        node = HammerDetectorNode()
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        rclpy.shutdown()


if __name__ == "__main__":
    main()