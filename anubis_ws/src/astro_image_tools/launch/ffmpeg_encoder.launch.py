from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    cam2 = Node(
        package='image_tools',
        executable='cam2image',
        name='cam2image',
        output='screen',
        parameters=[{
            'camera_device': 0,      # index -> /dev/video0
            'width': 1280,
            'height': 720,
            'frequency': 30.0,
            'show_image': False
        }],
        remappings=[('image', '/camera/image_raw')]
    )

    # ffmpeg params: these are the publisher (encoder) options.
    # Parameter names are "<base_topic>.ffmpeg.<param_name>" (see README).
    ffmpeg_params = {
        # Encoder selection: cpu/software encoders like 'libx264' or hw encoders like 'h264_nvenc', 'h264_vaapi'
        'image_raw.ffmpeg.encoder': 'libx264',

        # Comma-separated libav (ffmpeg) options in the form key:value
        # e.g. 'preset:veryfast,profile:baseline,crf:23'
        'image_raw.ffmpeg.encoder_av_options': 'preset:veryfast,profile:baseline,crf:23',

        # Number of frames between keyframes (larger -> better compression, more latency)
        'image_raw.ffmpeg.gop_size': 2,

        # Target bitrate in bits/s (e.g. 4 Mbps)
        'image_raw.ffmpeg.bit_rate': 400000,

        # Force pixel format used for encoding (typical values: 'yuv420p', 'yuvj420p', etc.)
        # This corresponds to the av_source_pixel_format in the encoder-decoder API.
        'image_raw.ffmpeg.pixel_format': 'yuv420p',

        # Maximum quantizer (encoder quality control). Larger -> worse image but smaller bitrate.
        'image_raw.ffmpeg.qmax': 60,

        # For debugging/perf measurement; set True to enable encoder perf measurements
        'image_raw.ffmpeg.encoder_measure_performance': False,

        # Additional optional tuning: if you want very low-latency settings you can add them via encoder_av_options:
        # e.g. 'image_raw.ffmpeg.encoder_av_options': 'preset:ultrafast,tune:zerolatency'
        #
        # NOTE: the README removed 'preset'/'tune'/'crf' as top-level params; they must be passed inside encoder_av_options.
        #
        # Example of alternative encoder and options (commented):
        # 'image_raw.ffmpeg.encoder': 'h264_nvenc',
        # 'image_raw.ffmpeg.encoder_av_options': 'preset:p1,profile:baseline,rc:vbr_hq,bitrate:4000k'
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
            ('in', '/camera/image_raw'),
            ('out', '/camera/image_raw/ffmpeg')
        ],
        # set ffmpeg parameters for the outgoing (ffmpeg) transport
        parameters=[ffmpeg_params]
    )

    return LaunchDescription([cam2, republish])
