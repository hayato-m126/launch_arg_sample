import launch
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    # args
    compare_str = LaunchConfiguration("compare_str", default="Hello World:")
    compare_str_arg = DeclareLaunchArgument(
        "compare_str", default_value="Hello World:", description="chatter compare string"
    )

    # talker node
    taker_node = Node(
        package="demo_nodes_cpp", executable="talker", output="screen", name="talker"
    )

    listener_node = Node(
        package="launch_arg_sample",
        executable="listener_node",
        output="screen",
        name="listner",
        parameters=[
            {
                "compare_str": compare_str,
            }
        ],
    )

    return launch.LaunchDescription(
        [
            compare_str_arg,
            taker_node,
            listener_node,
        ]
    )
