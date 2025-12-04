from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='image_transport',       # your package name
            executable='ffmpeg_image_transport',  # the node executable name
            name='ffmpeg_image_transport',
            output='screen',
            parameters=[{
                # Example parameters — adjust as needed
                'input_url': '/dev/video0',           # or 'rtsp://...', 'udp://...', etc.
                'output_topic': '/camera/image_raw',  # ROS topic to publish frames
                'fps': 30.0,
                'resolution': '1280x720'
            }],
            remappings=[
                ('/camera/image_raw', '/image_transport/output')
            ]
        )
    ])
