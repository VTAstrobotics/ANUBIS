from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
import os
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from launch.actions import ExecuteProcess

from launch.conditions import IfCondition, UnlessCondition

def generate_launch_description():

    ### Drive
    drive_share = get_package_share_directory('drive')
    drive_launch = os.path.join(drive_share, 'launch', 'drive.launch.py')


    ## Distributor
    pkg_share_distributor = get_package_share_directory('distributor')
    config_file_distributor = os.path.join(pkg_share_distributor, "include", "distributorconfig.yaml")
    distributor_node = Node(
        package="distributor",
        executable="distributor_node",
        name="distributor_node",
        output="screen",
        parameters=[config_file_distributor]
    )


    

    ### NAV2
    nav2_bringup_share = get_package_share_directory('nav2_bringup')
    our_nav_share = get_package_share_directory('navigation')
    nav2_params = os.path.join(our_nav_share, 'config', 'nav2_params.yaml')
    nav2_launch = os.path.join(nav2_bringup_share, 'launch', 'navigation_launch.py')

    ### JOY
    joy_node = Node(
        package="joy",
        executable="joy_node",
        name="joy_node",
        output="screen"
    )


    ### RTABMAP
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


    base_link_to_camera_link = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='base_to_camera_link_publisher',
        arguments=[
            '0.2', '0', '0.3', '0', '0', '0', 'base_link', 'camera_link'
        ]
    )

    can_startup = '/home/astrobotics/launch_scripts/can_startup.sh'

    run_can_startup = ExecuteProcess(
        cmd=['bash', can_startup],
        output='screen'
    )

    return LaunchDescription([
        IncludeLaunchDescription(PythonLaunchDescriptionSource(drive_launch)),
        distributor_node,
        joy_node,
        slam,
        base_link_to_camera_link,
        run_can_startup
    ])