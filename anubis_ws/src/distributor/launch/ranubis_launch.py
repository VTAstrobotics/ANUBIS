from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    pkg_share_motors = get_package_share_directory("motor_control")
    pkg_share_distributor = get_package_share_directory("distributor")
    config_file_motors = os.path.join(pkg_share_motors, "config", "kraken_params.yaml")
    config_file_distributor = os.path.join(pkg_share_distributor, "config", "distributorconfig.yaml")

    can_script = os.path.join(pkg_share_distributor, "scripts", "can_startup.sh")
    can_startup = ExecuteProcess(
        cmd=["bash", can_script],
        output="screen"
    )

    # List each node name defined in the YAML
    motor_nodes = ["kraken_front_left", "kraken_front_right"]

    motor_control_node = [
        Node(
            package="motor_control",
            executable="kraken_control_node",
            name=node_name,
            output="screen",
            parameters=[config_file_motors],
        )
        for node_name in motor_nodes
    ]

    distributor_node = Node(
        package="distributor",
        executable="distributor_node",
        name="distributor_node",
        output="screen",
        parameters=[config_file_distributor]
    )

    return LaunchDescription([distributor_node] + motor_control_node)