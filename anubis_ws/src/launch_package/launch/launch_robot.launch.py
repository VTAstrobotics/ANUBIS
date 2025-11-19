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

    # pkg_share_distributor = get_package_share_directory('distributor')
    # web_video_share = get_package_share_directory('web_video_server')

    # config_file_distributor = os.path.join(pkg_share_distributor, "include", "distributorconfig.yaml")
    nav2_bringup_share = get_package_share_directory('nav2_bringup')
    # our_nav_shar = get_package_share_directory('navigation')
    # nav2_params = os.path.join(our_nav_shar, 'config', 'nav2_params.yaml')

    # nav2_launch = os.path.join(nav2_bringup_share, 'launch', 'navigation_launch.py')


    # can_script = os.path.join(pkg_share_distributor, "scripts", "can_startup.sh")
    # can_startup = ExecuteProcess(
    #     cmd=["bash", can_script],
    #     output="screen"
    # )

    # distributor_node = Node(
    #     package="distributor",
    #     executable="distributor_node",
    #     name="distributor_node",
    #     output="screen",
    #     parameters=[config_file_distributor]
    # )
    teleop_node = Node(
        package="teleop",
        executable="teleop_node",
        name="teleop_node",
        output="screen"
    )

    drive_node = Node(
        package="drive",
        executable="drive_node",
        name="drive_node",
        output="screen"
    )

    joy_node = Node(
        package="joy",
        executable="joy_node",
        name="joy_node",
        output="screen"
    )


    ###RTABMAP
    parameters={
          'frame_id':'base_link',
        #   'use_sim_time':True,
          'subscribe_depth':True,
          'use_action_for_goal':True,
          'Reg/Force3DoF':'true',
          'Grid/RayTracing':'true', # Fill empty space
          'Grid/3D':'false', # Use 2D occupancy
          'Grid/RangeMax':'5',
          'Grid/NormalsSegmentation':'false', # Use passthrough filter to detect obstacles
          'Grid/MaxGroundHeight':'0.05', # All points above 5 cm are obstacles
          'Grid/MaxObstacleHeight':'0.4',  # All points over 1 meter are ignored
          'wait_for_transform_duration': 1,
          'Optimizer/GravitySigma':'0', # Disable imu constraints (we are already in 2D)
          'Grid/FrameId':'map'
    }
    remappings=[
            ('rgb/image', 'zed/rgb/color/rect/image'),
            ('rgb/camera_info', '/zed/zed_node/camera_info'),
            ('depth/image', '/zed/zed_node/point_cloud/cloud_registered'),
            ('odom', '/odom'),
            # ('gps/fix', '/gps/data')
          ]

        # SLAM mode:
    slam = Node(
            package='rtabmap_slam', executable='rtabmap', output='screen',
            parameters=[parameters],
            remappings=remappings,
            arguments=['-d'])

    web_video_server_node = Node(
        package="web_video_server",
        executable="web_video_server_node",
        name="web_video_server",
        output="screen"
    )

    base_link_to_camera_link = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='base_to_camera_link_publisher',
        arguments=[
            '0.2', '0', '0.3', '0', '0', '0', 'base_link', 'camera_link'
        ]
    )

    return LaunchDescription([
        teleop_node,
        drive_node,
        joy_node,
        slam,
        web_video_server_node,
        base_link_to_camera_link
    ])