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
    # calibration command
    # ros2 run camera_calibration cameracalibrator --size 8x6 --square 0.03529 image:=/webcam/image_raw camera:=/webcam

    # each camera will require these 2 nodes to be started for it to work properly.
    webcam_v4l2 = Node(
        package="v4l2_camera",
        executable="v4l2_camera_node",
        name="Front_Camera_Driver",
        output="screen",
        namespace="webcam",
        parameters=[{
            "video_device": "/dev/v4l/by-id/usb-Framework_Laptop_Webcam_Module__2nd_Gen__FRANJBCHA1537100EB-video-index0",
            "image_size": [640, 480],
    #    {
            "image_raw.ffmpeg.qmax": 1,  # high quality
            "image_raw.ffmpeg.bit_rate": 1000000,  # required!
            "image_raw.ffmpeg.gop_size": 1,
            "image_raw.ffmpeg.encoder": "libx264",
        # },
        }]
        # using the video device from v4l means we access the same camera each time and the driver exposes what camera is active on a node via the 
        # video device parameter via ros2. This lets us actually access the camera easily compared to /dev/video* ids.
    )
    cameras.append(webcam_v4l2)
    aruco_webcam = Node(
        package="pose_estimation",
        executable="v4l2_aruco_node",
        name="webcam_camera_aruco",
        output="screen",
        namespace="webcam",
        parameters=[{
            "camera_name": "/dev/v4l/by-id/usb-046d_Brio_101_2450APR8ZF68-video-index0"
        }]
        # using the video device from v4l means we access the same camera each time and the driver exposes what camera is active on a node via the 
        # video device parameter via ros2. This lets us actually access the camera easily compared to /dev/video* ids.
    )
    # cameras.append(aruco_webcam)

    compressed_transport = Node(
        package="image_transport",
        executable='republish',
        name="webcam_compressor",
        output = "screen",
        namespace="webcam",
        arguments=['raw', 'ffmpeg'], # a bug 
        # theres a bug https://robotics.stackexchange.com/questions/116905/image-transport-parameters-in-yaml-files
        parameters=[
            
            {"in_transport": "raw"},
            {"out_transport": "ffmpeg"},
 
        ],
        remappings=[
            ("in", "image_raw"),
            ("out", "image_raw")
        ]
        # arguments=['raw', 'ffmpeg', '--ros-args', 
        #                '--remap', 'in:=webcam/image_raw',
        #                '--remap', 'out:=ffmpeg']
        
    )
    # cameras.append(compressed_transport)
    web_video_server_node = Node(
        package="web_video_server",
        executable="web_video_server_node",
        name="web_video_server",
        output="screen"
    )
    # cameras.append(web_video_server_node)
    return LaunchDescription(cameras)