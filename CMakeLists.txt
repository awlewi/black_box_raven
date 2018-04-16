cmake_minimum_required(VERSION 2.8.3)
project(black_box_raven)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS 
  roscpp rospy std_msgs 
  geometry_msgs message_generation
  raven_2)

## Add in message and service files
#add_message_files(FILES raven_automove.msg raven_state.msg)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs geometry_msgs)

## Declare a catkin package
catkin_package(CATKIN_DEPENDS message_runtime)

## Build listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(listenerBlackBox 
  src/listener.cpp  
#  src/Raven_Controller.cpp 
#  src/Raven_PathPlanner.cpp
)
target_link_libraries(listenerBlackBox ${catkin_LIBRARIES})
add_dependencies(listenerBlackBox black_box_raven_generate_messages_cpp)