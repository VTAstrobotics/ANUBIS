from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from ament_index_python.packages import get_package_share_directory
from launch.substitutions import LaunchConfiguration

def generate_launch_description():

    republisher_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            PathJoinSubstitution([
                get_package_share_directory('astro_image_tools'),
                'launch',
                'republish.launch.py'
            ])
        ]),
        launch_arguments={
            'camera': '/camera/Serial_2451AP6M3MQ8/decoder',
            'image_topic': 'out/ffmpeg',
            'in_transport': 'ffmpeg',
            'out_transport': 'raw'
        }.items(),
    )

    return LaunchDescription([
        republisher_launch,
    ])
