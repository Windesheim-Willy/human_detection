cmake_minimum_required(VERSION 2.8.3)

# Project name
project(human_detection)

## Add support for C++11, supported in ROS Kinetic and newer
# add_definitions(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  	roscpp
  	cv_bridge
)

find_package(OpenCV REQUIRED)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(human_detection

	main.cpp
	Tracking/Rectangle.cpp
    Tracking/RectangleTracker.cpp
)

target_link_libraries(human_detection 

    ${catkin_LIBRARIES}
    ${Boost_INCLUDE_DIRS}
    ${OpenCV_LIBRARIES}
)