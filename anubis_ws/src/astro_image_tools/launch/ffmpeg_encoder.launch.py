from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import PathJoinSubstitution
from ament_index_python.packages import get_package_share_directory
from launch.substitutions import LaunchConfiguration

def generate_launch_description():

    #ros2 run image_transport republish ffmpeg raw --ros-args -r /in/ffmpeg:=/out/ffmpeg -r /out:=/decoded_raw --log-level debug
    # for testing

    # ffmpeg params: these are the publisher (encoder) options.
    # Parameter names are "<base_topic>.ffmpeg.<param_name>" (see README).
    ffmpeg_params = {
    'out.ffmpeg.encoder': 'libx264',
    'out.ffmpeg.encoder_av_options': 'preset:superfast,profile:baseline,crf:38,tune:zerolatency',
    'out.ffmpeg.gop_size': 2,
    'out.ffmpeg.bit_rate': 4000000,  # 4 Mbps
    'out.ffmpeg.pixel_format': 'yuv420p',
    'out.ffmpeg.qmax': 150,
    'out.ffmpeg.encoder_measure_performance': False,
    }



    republish = Node(
        package='image_transport',
        executable='republish',
        name='republish_raw_to_ffmpeg',
        output='screen',
        # positional args: <in_transport> <out_transport>
        arguments=['raw', 'ffmpeg'],
        # remap the 'in' and 'out' base topic names expected by republish
        remappings=[
            ('in', '/usbcam_image_camera'),
            ('out', '/ffmpeg')
        ],
        # set ffmpeg parameters for the outgoing (ffmpeg) transport
        parameters=[ffmpeg_params]
    )

    return LaunchDescription([
        republisher_launch,
    ])
