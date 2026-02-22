import os

from ament_index_python.packages import get_package_share_directory


from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node

def generate_launch_description():
    spawn_sampler = Node(package="sampler",            
        executable="sampler_node",
        name="sampler_node",
        parameters=[{"use_sim_time": False},
                    ]
    )


    spawn_auger_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "auger_motor",
    parameters=[{"motor_name": "auger"},
                {"can_interface": "can1"},
                {"can_id": 23},
                {"control_topic": "/auger/control"},
                {"status_topic": "/auger/status"},
                {"health_topic": "/auger/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=right_motor_controller"]
    )
    
    spawn_carousel_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "carousel_motor",
    parameters=[{"motor_name": "carousel"},
                {"can_interface": "can1"},
                {"can_id": 47},
                {"control_topic": "/carousel/control"},
                {"status_topic": "/carousel/status"},
                {"health_topic": "/carousel/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=right_motor_controller"]
    )

     # calibration command

        # using the video device from v4l means we access the same camera each time and the driver exposes what camera is active on a node via the 
        # video device parameter via ros2. This lets us actually access the camera easily compared to /dev/video* ids.


    return LaunchDescription([
        spawn_sampler,
        spawn_carousel_motor
        # spawn_auger_motor
        # aruco_webcam
    ])

