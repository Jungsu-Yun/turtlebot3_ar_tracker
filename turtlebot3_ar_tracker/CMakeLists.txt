cmake_minimum_required(VERSION 2.8.3)
project(turtlebot3_ar_tracker)

find_package(catkin REQUIRED COMPONENTS
  ar_track_alvar
  ar_track_alvar_msgs
  geometry_msgs
  roscpp
  std_msgs
  tf
)

catkin_package(

)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)
add_executable(${PROJECT_NAME}_node src/main.cpp src/Subscriber.cpp src/Vec.cpp src/Vec.h)
target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES}
)