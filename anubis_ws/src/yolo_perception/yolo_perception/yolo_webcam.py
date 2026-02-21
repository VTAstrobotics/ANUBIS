import os
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from vision_msgs.msg import Detection2D, Detection2DArray, ObjectHypothesisWithPose
from cv_bridge import CvBridge
import cv2
from inference_sdk import InferenceHTTPClient


class HammerDetectorNode(Node):
    def __init__(self):
        super().__init__("hammer_detector_node")

        self.declare_parameter("api_key", os.environ.get("ROBOFLOW_API_KEY", ""))
        self.declare_parameter("model_id", "astro2026-urc/3")
        self.declare_parameter("confidence_threshold", 0.50)
        self.declare_parameter("image_topic", "/camera/image_raw")
        self.declare_parameter("publish_annotated", True)

        api_key            = self.get_parameter("api_key").value
        model_id           = self.get_parameter("model_id").value
        self.conf          = self.get_parameter("confidence_threshold").value
        img_topic          = self.get_parameter("image_topic").value
        self.pub_annotated = self.get_parameter("publish_annotated").value

        if not api_key:
            self.get_logger().error("No ROBOFLOW_API_KEY set!")
            raise RuntimeError("Missing Roboflow API key")

        self.client   = InferenceHTTPClient(api_url="https://detect.roboflow.com", api_key=api_key)
        self.model_id = model_id
        self.bridge   = CvBridge()

        self.sub_image      = self.create_subscription(Image, img_topic, self.image_callback, 10)
        self.pub_detections = self.create_publisher(Detection2DArray, "/hammer_detections", 10)

        if self.pub_annotated:
            self.pub_debug = self.create_publisher(Image, "/hammer_detections/debug_image", 10)

        self.get_logger().info(f"Listening on {img_topic} | model: {model_id}")

    def image_callback(self, msg: Image):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding="bgr8")
        except Exception as e:
            self.get_logger().error(f"cv_bridge error: {e}")
            return

        try:
            result = self.client.infer(cv_image, model_id=self.model_id)
        except Exception as e:
            self.get_logger().error(f"Inference error: {e}")
            return

        predictions = result.get("predictions", [])

        det_array        = Detection2DArray()
        det_array.header = msg.header

        for pred in predictions:
            conf = pred.get("confidence", 0.0)
            if conf < self.conf:
                continue

            det = Detection2D()
            det.header = msg.header
            det.bbox.center.position.x = float(pred["x"])
            det.bbox.center.position.y = float(pred["y"])
            det.bbox.size_x = float(pred["width"])
            det.bbox.size_y = float(pred["height"])

            hyp = ObjectHypothesisWithPose()
            hyp.hypothesis.class_id = pred.get("class", "Orange Hammer")
            hyp.hypothesis.score    = conf
            det.results.append(hyp)
            det_array.detections.append(det)

        self.pub_detections.publish(det_array)
        self.get_logger().info(f"Detected {len(det_array.detections)} object(s)")

        if self.pub_annotated:
            annotated = self._draw(cv_image.copy(), predictions)
            try:
                dbg = self.bridge.cv2_to_imgmsg(annotated, encoding="bgr8")
                dbg.header = msg.header
                self.pub_debug.publish(dbg)
            except Exception as e:
                self.get_logger().error(f"Debug image error: {e}")

    def _draw(self, image, predictions):
        for pred in predictions:
            if pred.get("confidence", 0.0) < self.conf:
                continue
            cx, cy = int(pred["x"]), int(pred["y"])
            w,  h  = int(pred["width"]), int(pred["height"])
            x1, y1 = cx - w // 2, cy - h // 2
            x2, y2 = cx + w // 2, cy + h // 2
            cv2.rectangle(image, (x1, y1), (x2, y2), (0, 165, 255), 2)
            label = f"{pred.get('class','?')} {pred.get('confidence',0):.0%}"
            cv2.putText(image, label, (x1, y1 - 8), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 165, 255), 2)
        return image


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
