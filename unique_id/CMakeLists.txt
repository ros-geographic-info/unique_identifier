cmake_minimum_required(VERSION 3.5)

project(unique_id)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wpedantic")
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(uuid_msgs REQUIRED)
find_package(Boost REQUIRED)

include_directories("include")
add_library(${PROJECT_NAME} "include/unique_id/unique_id.h")
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

ament_target_dependencies(${PROJECT_NAME} "rclcpp" "rclpy" "uuid_msgs" "Boost")
ament_export_include_directories("include")
ament_export_libraries(${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_cmake_gmock REQUIRED)
  find_package(ament_lint_auto REQUIRED)

  ament_lint_auto_find_test_dependencies()

  ament_add_gmock(first_test_${PROJECT_NAME} tests/test_unique_id.cpp)
  ament_target_dependencies(first_test_unique_id "${PROJECT_NAME}" "uuid_msgs" "Boost")

  ament_add_gmock(second_test_${PROJECT_NAME} tests/second_test_unique_id.cpp)
  ament_target_dependencies(second_test_unique_id "${PROJECT_NAME}" "uuid_msgs" "Boost")

  ament_add_nose_test(nose_test_${PROJECT_NAME} "tests/test_${PROJECT_NAME}.py" TIMEOUT 60)

  ament_export_dependencies(ament_cmake_gmock)
endif()

ament_package()

