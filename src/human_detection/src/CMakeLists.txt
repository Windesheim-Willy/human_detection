cmake_minimum_required(VERSION 2.8.3)

# Project name
project(human_detection)

## Add support for C++11, supported in ROS Kinetic and newer
# add_definitions(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(OpenCV REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  	roscpp
  	cv_bridge
    rospy
    std_msgs
    genmsg
    message_generation  
)

## Add project generated messages (do so before building own code)
add_message_files(
  FILES
  Person.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs 
)

catkin_package(
  CATKIN_DEPENDS 
  message_runtime
  human_detection_generate_messages_cpp
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(human_detection

	main.cpp
	Tracking/Rectangle.cpp
  Tracking/RectangleTracker.cpp
  OpenCVTracking.cpp
)

add_dependencies(human_detection 

  human_detection_generate_messages_cpp 
  ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(human_detection 

    ${catkin_LIBRARIES}
    ${Boost_INCLUDE_DIRS}
    ${OpenCV_LIBRARIES}
)

install( TARGETS
    human_detection
    DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)