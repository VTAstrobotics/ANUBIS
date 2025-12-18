import dis
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

    ### Reaper Description
    reaper_description_share = get_package_share_directory('reaper_description')
    reaper_description_launch = os.path.join(reaper_description_share, 'launch', 'launch.py')


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


    ### RTABMAP
    parameters={
          'frame_id':'base_link',
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
          'Grid/FrameId':'map',
          'Cloud/DownsamplingStep': '4',
          'Rtabmap/DetectionRate': '1',
          'Kp/MaxFeatures': '400',
          'Rtabmap/LoopThr': '0.11',
          'RGBD/DepthDecimation' : 4,
          "Mem/STMSize": "30",
          "Mem/LTMSize": "200"

    }
    remappings=[
            ('rgb/image', 'zed/zed_node/rgb/color/rect/image'),
            ('rgb/camera_info', '/zed/zed_node/rgb/color/rect/camera_info'),
            ('depth/image', '/zed/zed_node/depth/depth_registered'),
            ('odom', '/odom'),
            # ('gps/fix', '/gps/data')
          ]

        # SLAM mode:
    slam = Node(
            package='rtabmap_slam', executable='rtabmap', output='screen',
            parameters=[parameters],
            remappings=remappings,
            arguments=['-d'])

    ukf_dir = get_package_share_directory("ukf_launch")
    ukf_launch =  os.path.join(ukf_dir, 'launch', 'ukf.launch.py')

    urdf_dir = get_package_share_directory("reaper_description")
    urdf_launch =  os.path.join(urdf_dir, 'launch', 'launch.py')

    try: 
        zed_wrapper_dir = get_package_share_directory("zed_wrapper")
        zed_launch =  os.path.join(zed_wrapper_dir, 'launch', 'zed_camera.launch.py')
        found_zed = True
    except:
        found_zed = False


    return LaunchDescription([
        IncludeLaunchDescription(PythonLaunchDescriptionSource(drive_launch)),
        IncludeLaunchDescription(PythonLaunchDescriptionSource(reaper_description_launch)),
        IncludeLaunchDescription(PythonLaunchDescriptionSource(ukf_launch)),
        IncludeLaunchDescription(PythonLaunchDescriptionSource(zed_launch)),

        # IncludeLaunchDescription(PythonLaunchDescriptionSource(nav2_launch), 
        #                          launch_arguments={
        #                             'use_sim_time': 'true',
        #                             'params_file': nav2_params,
        #                         }.items()
        #                     ),
        distributor_node,
        slam,
    ])