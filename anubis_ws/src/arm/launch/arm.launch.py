import os

from ament_index_python.packages import get_package_share_directory


from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node


# TODO: change logic to spawn in arm motors
    # - 6 joint krakens
def generate_launch_description():
    # spawn_arm_hardware_node = Node(package="arm",            
    #     executable="arm_hardware_node",
    #     name="arm_hardware_node"
    # )

    spawn_arm_joy_control_noik = Node(package="arm",            
        executable="arm_joy_control_node_noik",
        name="arm_joy_control_node_noik"
    )
    spawn_base_lat_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},  
                {"can_id": 30},
                {"control_topic": "/base_lat_left/control"},
                {"status_topic": "/base_lat_left/status"},
                {"health_topic": "/base_lat_left/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=base_left_motor_controller"]
    )
    
    spawn_left_base_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 32},
                {"control_topic": "/base_joint_left/control"},
                {"status_topic": "/base_joint_left/status"},
                {"health_topic": "/base_joint_left/health"},
                {"inversion": True},
                {"kG": 0.45}], # it is possible that we need kp as well
    arguments=["--ros-args",
               "-r",
               "__node:=base_left_motor_controller"]
    )

    spawn_right_base_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 31},
                {"control_topic": "/base_joint_right/control"},
                {"status_topic": "/base_joint_right/status"},
                {"health_topic": "/base_right/health"},
                {"inversion": True},
                {"kG": 0.45}],
    arguments=["--ros-args",
               "-r",
               "__node:=base_right_motor_controller"]
    )

    spawn_elbow_left_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 34},
                {"control_topic": "/elbow_left/control"},
                {"status_topic": "/elbow_left/status"},
                {"health_topic": "/elbow_left/health"},
                {"inversion": False},
                {"kG": 0.25}],
    arguments=["--ros-args",
               "-r",
               "__node:=elbow_left_motor_controller"]
    )

    spawn_elbow_right_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 33},
                {"control_topic": "/elbow_right/control"},
                {"status_topic": "/elbow_right/status"},
                {"health_topic": "/elbow_right/health"},
                {"inversion": True},
                {"kG": 0.25}],
    arguments=["--ros-args",
               "-r",
               "__node:=elbow_right_motor_controller"]
    )



    #TODO: assign proper CAN ids
    spawn_end_effector_left_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 24},
                {"control_topic": "/end_effector_left/control"},
                {"status_topic": "/end_effector_left/status"},
                {"health_topic": "/end_effector_left/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=end_effector_left_motor_controller"]
    )

    spawn_end_effector_right_motor = Node(package = "motor_control",
    executable = "kraken_control_node",
    name = "kraken_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 25},
                {"control_topic": "/end_effector_right/control"},
                {"status_topic": "/end_effector_right/status"},
                {"health_topic": "/base_end_effector_rightleft/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=end_effector_right_motor_controller"]
    )

    spawn_grabber = Node(package = "motor_control",
    executable = "sparkmax_control_node",
    name = "sparkmax_control_node",
    parameters=[{"motor_name": "left_motor"},
                {"can_interface": "can1"},
                {"can_id": 11}, 
                {"control_topic": "/grabber/control"},
                {"status_topic": "/grabber/status"},
                {"health_topic": "/grabber/health"}],
    arguments=["--ros-args",
               "-r",
               "__node:=grabber"]
    )

    return LaunchDescription([
        spawn_arm_joy_control_noik,
        spawn_base_lat_motor,
        spawn_left_base_motor,
        spawn_right_base_motor,
        spawn_elbow_right_motor,
        spawn_elbow_left_motor,
    ])

