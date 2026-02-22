import os

from ament_index_python.packages import get_package_share_directory


from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node

def generate_launch_description():
    spawn_drive = Node(package="drive",            
        executable="drive_node",
        name="drive_node",
        parameters=[{"use_sim_time": False},
                    ]
    )
    
    spawn_left_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_front"},
                {"can_interface": "can1"},
                {"can_id": 48},
                {"control_topic": "/left_front/control"},
                {"status_topic": "/left_front/status"},
                {"health_topic": "/left_front/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=left_motor_controller"]
    )
    spawn_left_back__motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_back"},
                {"can_interface": "can1"},
                {"can_id": 44},
                {"control_topic": "/left_back/control"},
                {"status_topic": "/left_back/status"},
                {"health_topic": "/left_back/health"}],
    arguments=["--ros-args",
            "-r",
            "__node:=left_motor_controller"]
)


    spawn_right_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "right_front"},
                {"can_interface": "can1"},
                {"can_id": 46},
                {"control_topic": "/right_front/control"},
                {"status_topic": "/right_front/status"},
                {"health_topic": "/right_front/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=right_motor_controller"]
    )
    
    spawn_right_back_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "right_back"},
                {"can_interface": "can1"},
                {"can_id": 45},
                {"control_topic": "/right_back/control"},
                {"status_topic": "/right_back/status"},
                {"health_topic": "/right_back/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=right_motor_controller"]
    )

    return LaunchDescription([
        spawn_drive,
        spawn_left_motor,
        spawn_right_motor,
        spawn_left_back__motor,
        spawn_right_back_motor
    ])

