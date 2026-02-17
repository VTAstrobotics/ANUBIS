import os

from ament_index_python.packages import get_package_share_directory


from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node


# TODO: change logic to spawn in arm motors
    # - 6 joint krakens
def generate_launch_description():
    spawn_arm_hardware_node = Node(package="arm",            
        executable="arm_hardware_node",
        name="arm_hardware_node"
    )
    
    spawn_left_base_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 20},
                {"control_topic": "/base_left/control"},
                {"status_topic": "/base_left/status"},
                {"health_topic": "/base_left/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=base_left_motor_controller"]
    )

    spawn_right_base_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 21},
                {"control_topic": "/base_right/control"},
                {"status_topic": "/base_right/status"},
                {"health_topic": "/base_right/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=base_right_motor_controller"]
    )

    spawn_elbow_left_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 22},
                {"control_topic": "/elbow_left/control"},
                {"status_topic": "/elbow_left/status"},
                {"health_topic": "/elbow_left/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=elbow_left_motor_controller"]
    )

    spawn_midde_right_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 23},
                {"control_topic": "/elbow_right/control"},
                {"status_topic": "/elbow_right/status"},
                {"health_topic": "/elbow_right/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=elbow_right_motor_controller"]
    )

    spawn_wrist_left_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 24},
                {"control_topic": "/wrist_left/control"},
                {"status_topic": "/wrist_left/status"},
                {"health_topic": "/wrist_left/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=wrist_left_motor_controller"]
    )

    spawn_wrist_right_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 25},
                {"control_topic": "/wrist_right/control"},
                {"status_topic": "/wrist_right/status"},
                {"health_topic": "/base_wrist_rightleft/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=wrist_right_motor_controller"]
    )

    return LaunchDescription([
    spawn_arm_hardware_node,           
        spawn_wrist_left_motor,
        spawn_wrist_right_motor,
        spawn_left_base_motor,
        spawn_right_base_motor,
        spawn_elbow_left_motor,
        spawn_midde_right_motor
    ])

