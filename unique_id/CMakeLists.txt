##############################################################################
# CMake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(unique_id)

##############################################################################
# Find Packages
##############################################################################

# System Dependencies
find_package(Boost REQUIRED)  # uuid, note - not a package/component of its own

# ROS Dependencies
find_package(ament_cmake_python REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(uuid_msgs REQUIRED)

##############################################################################
# Project Configuration
##############################################################################

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

##############################################################################
# Header Library
##############################################################################

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
    ${Boost_LIBRARIES}
)

# note: quotes to capture multiple directories
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    "$<BUILD_INTERFACE:${uuid_msgs_INCLUDE_DIRS}>"
    "$<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>"
    $<INSTALL_INTERFACE:include>
    "$<INSTALL_INTERFACE:include:${uuid_msgs_INCLUDE_DIRS}>"
    "$<INSTALL_INTERFACE:include:${Boost_INCLUDE_DIRS}>"
)


##############################################################################
# Tests
##############################################################################

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  find_package(ament_cmake_nose REQUIRED)
  add_subdirectory(tests)
endif()

##############################################################################
# C++ Project Installation
##############################################################################

# Downstream projects can link to the 'unique_id::unique_id' target.
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

# Install the headers
install(
  DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
)

##############################################################################
# Python Project Installation
##############################################################################

ament_python_install_package(${PROJECT_NAME})

##############################################################################
# Ament Exports
##############################################################################

ament_export_interfaces(${PROJECT_NAME})
ament_export_dependencies(
    uuid_msgs
)
ament_package()
