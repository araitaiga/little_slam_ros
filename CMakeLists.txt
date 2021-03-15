cmake_minimum_required(VERSION 3.0.2)
project(little_slam_ros)

add_compile_options(-std=c++11)
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  pcl_ros
  roscpp
  sensor_msgs
  nav_msgs
  std_msgs
  tf
  tf2
  tf2_ros
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES little_slam_ros
#  CATKIN_DEPENDS geometry_msgs pcl_ros roscpp sensor_msgs std_msgs tf tf2 tf2_ros
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(little_slam_ros src/little_slam_node.cpp src/slam_launcher.cpp src/slam_frontend.cpp src/scan_matcher.cpp src/map_util.cpp)

target_link_libraries(little_slam_ros
  ${catkin_LIBRARIES}
)
