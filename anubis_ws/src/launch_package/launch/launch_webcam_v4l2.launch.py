from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
import os
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from launch.actions import ExecuteProcess

from launch.conditions import IfCondition, UnlessCondition

def generate_launch_description():
    # drive_share = get_package_share_directory('drive')
    pkg_share_distributor = get_package_share_directory('distributor')
    # web_video_share = get_package_share_directory('web_video_server')

    config_file_distributor = os.path.join(pkg_share_distributor, "config", "distributorconfig.yaml")

    nav2_bringup_share = get_package_share_directory('nav2_bringup')
    # our_nav_shar = get_package_share_directory('navigation')
    # nav2_params = os.path.join(our_nav_shar, 'config', 'nav2_params.yaml')

    # nav2_launch = os.path.join(nav2_bringup_share, 'launch', 'navigation_launch.py')
    # parameters={
    #       'frame_id':'base_link',
    #       'use_sim_time':True,
    #       'subscribe_depth':True,
    #       'use_action_for_goal':True,
    #       'Reg/Force3DoF':'true',
    #       'Grid/RayTracing':'true', # Fill empty space
    #       'Grid/3D':'false', # Use 2D occupancy
    #       'Grid/RangeMax':'5',
    #       'Grid/NormalsSegmentation':'false', # Use passthrough filter to detect obstacles
    #       'Grid/MaxGroundHeight':'0.05', # All points above 5 cm are obstacles
    #       'Grid/MaxObstacleHeight':'0.4',  # All points over 1 meter are ignored
    #       'wait_for_transform_duration': 1,
    #       'Optimizer/GravitySigma':'0', # Disable imu constraints (we are already in 2D)
    #       'Grid/FrameId':'map'
    # }

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