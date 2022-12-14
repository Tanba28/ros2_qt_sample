cmake_minimum_required(VERSION 3.8)
project(ros2_qt_int_listener)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

set(ROS2 true)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/qt)
add_executable(ros2_qt_int_listener src/main.cpp)

target_link_libraries(ros2_qt_int_listener qt)

ament_target_dependencies(ros2_qt_int_listener
  rclcpp
  std_msgs)

install(TARGETS
  ros2_qt_int_listener
  DESTINATION lib/${PROJECT_NAME})
  
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
