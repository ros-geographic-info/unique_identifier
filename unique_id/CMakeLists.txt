cmake_minimum_required(VERSION 3.5)
project(unique_id)

# Add support for C++11
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(uuid_msgs REQUIRED)
find_package(rclpy REQUIRED)

set(INCLUDE_DIRS include ${ament_cmake_INCLUDE_DIRS} ${rclcpp_INCLUDE_DIRS}
  ${uuid_msgs_INCLUDE_DIRS} ${rclpy_INCLUDE_DIRS})
include_directories(${INCLUDE_DIRS})

set(LIBRARY_DIRS ${ament_cmake_LIBRARY_DIRS} ${rclcpp_LIBRARY_DIRS}
  ${uuid_msgs_LIBRARY_DIRS} ${rclpy_LIBRARY_DIRS})

link_directories(${LIBRARY_DIRS})

set(LIBS ${ament_cmake_LIBRARIES} ${rclcpp_LIBRARIES} ${uuid_msgs_LIBRARIES}
  ${rclpy_LIBRARIES})

find_package(Boost REQUIRED)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME})

# unit tests
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

ament_export_dependencies(ament_cmake)
ament_export_dependencies(rclcpp)
ament_export_dependencies(uuid_msgs)
ament_export_dependencies(rclpy)
ament_export_include_directories(${INCLUDE_DIRS})

ament_package()
