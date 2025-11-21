import os
import launch
import launch_ros
from ament_index_python.packages import get_package_share_directory
from launch_param_builder import ParameterBuilder
from moveit_configs_utils import MoveItConfigsBuilder
from launch_ros.actions import Node


def generate_launch_description():
    moveit_config = (
        MoveItConfigsBuilder(robot_name="visual", package_name="moveit_servo")
        .robot_description(file_path="config/urdf/braccio_arm.urdf")
        .joint_limits(file_path="config/joint_limits.yaml") # need to find this file
        .robot_description_kinematics()
        .to_moveit_configs()
    )

    # Get parameters for the Servo node
    servo_params = {
        "moveit_servo": ParameterBuilder("moveit_servo")
        .yaml("config/braccio_simulated_config.yaml")
        .to_dict()
    }

    # This sets the update rate and planning group name for the acceleration limiting filter.
    acceleration_filter_update_period = {"update_period": 0.01}
    planning_group_name = {"planning_group_name": "braccio_arm"}

    servo_node = launch_ros.actions.Node(
        package="moveit_servo",
        executable="servo_node",
        parameters=[
            servo_params,
            acceleration_filter_update_period,
            planning_group_name,
            moveit_config.robot_description,
            moveit_config.robot_description_semantic,
            moveit_config.robot_description_kinematics,
            moveit_config.joint_limits
        ],
        output="screen",
    )

    # cartesian_limits_params = {
    #     "robot_description_planning": {
    #         "cartesian_limits": {
    #             "max_trans_vel": 0.4,   
    #             "max_trans_acc": 0.4,   
    #             "max_trans_dec": 0.4,   
    #             "max_rot_vel": 1.6,     
    #             "max_rot_acc": 1.6,     
    #         }
    #     }
    # }
    # move_group_node = Node(
    #     package="moveit_ros_move_group",
    #     executable="move_group",
    #     output="screen",
    #     parameters=[
    #         moveit_config.robot_description,
    #         moveit_config.robot_description_semantic,
    #         moveit_config.robot_description_kinematics,
    #         moveit_config.joint_limits,
    #         moveit_config.planning_pipelines,  
    #         cartesian_limits_params,           
    #     ],
    # )

    return launch.LaunchDescription(
        [
            servo_node,
            # move_group_node
        ]
    )
