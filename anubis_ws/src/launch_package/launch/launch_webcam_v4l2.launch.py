from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
import os
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from launch.actions import ExecuteProcess

from launch.conditions import IfCondition, UnlessCondition

def generate_launch_description():
    cameras = []

    webcam_v4l2 = Node(
        package="v4l2_camera",
        executable="v4l2_camera_node",
        name="webcam_camera_driver",
        output="screen",
        parameters=[{
            "video_device": "/dev/v4l/by-id/usb-Framework_Laptop_Webcam_Module__2nd_Gen__FRANJBCHA1537100EB-video-index0"

        }]
        # using the video device from v4l means we access the same camera each time and the driver exposes what camera is active on a node via the 
        # video device parameter via ros2. This lets us actually access the camera easily compared to /dev/video* ids.
    )
    cameras.append(webcam_v4l2)


    web_video_server_node = Node(
        package="web_video_server",
        executable="web_video_server_node",
        name="web_video_server",
        output="screen"
    )
    # cameras.append(web_video_server_node)
    return LaunchDescription(cameras)