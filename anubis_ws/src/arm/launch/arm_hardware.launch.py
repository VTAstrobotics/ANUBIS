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
    
    spawn_left_lat_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 20},
                {"control_topic": "/base_lat_left/control"},
                {"status_topic": "/base_lat_left/status"},
                {"health_topic": "/base_lat_left/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=base_lat_left_motor_controller"]
    )

    spawn_right_lat_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 21},
                {"control_topic": "/base_lat_right/control"},
                {"status_topic": "/base_lat_right/status"},
                {"health_topic": "/base_lat_right/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=base_lat_right_motor_controller"]
    )

    spawn_base_joint_left_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 22},
                {"control_topic": "/base_joint_left/control"},
                {"status_topic": "/base_joint_left/status"},
                {"health_topic": "/base_joint_left/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=base_joint_left_motor_controller"]
    )

    spawn_base_joint_right_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 23},
                {"control_topic": "/base_joint_right/control"},
                {"status_topic": "/base_joint_right/status"},
                {"health_topic": "/base_joint_right/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=base_joint_right_motor_controller"]
    )

    spawn_elbow_left_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 24},
                {"control_topic": "/elbow_left/control"},
                {"status_topic": "/elbow_left/status"},
                {"health_topic": "/elbow_left/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=elbow_left_motor_controller"]
    )

    spawn_elbow_right_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 25},
                {"control_topic": "/elbow_right/control"},
                {"status_topic": "/elbow_right/status"},
                {"health_topic": "/elbow_wrist_rightleft/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=elbow_right_motor_controller"]
    )

    spawn_ee_left_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 25},
                {"control_topic": "/end_effector_left/control"},
                {"status_topic": "/end_effector_left/status"},
                {"health_topic": "/end_effector_left/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=end_effector_right_motor_controller"]
    )

    spawn_ee_right_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 25},
                {"control_topic": "/end_effector_right/control"},
                {"status_topic": "/end_effector_right/status"},
                {"health_topic": "/end_effector_right/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=end_effector_right_motor_controller"]
    )

    return LaunchDescription([
        spawn_base_joint_left_motor,
        spawn_base_joint_right_motor,
        
        spawn_left_lat_motor,
        spawn_right_lat_motor,

        spawn_elbow_left_motor,
        spawn_elbow_right_motor,

        spawn_ee_left_motor,
        spawn_ee_right_motor

    ])

