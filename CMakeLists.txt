cmake_minimum_required(VERSION 3.0.2)
project(string2marker)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  visualization_msgs
)

catkin_package(
    CATKIN_DEPENDS
        roscpp
        std_msgs
        visualization_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(string_to_text_marker src/string_to_text_marker_node.cpp)
target_link_libraries(string_to_text_marker ${catkin_LIBRARIES})