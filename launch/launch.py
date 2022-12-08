from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='ros2_qt_int_listener',
            executable='ros2_qt_int_listener',
            name='listener'
        ),
        Node(
            package='ros2_qt_int_sender',
            executable='ros2_qt_int_sender',
            name='sender'
        )
    ])