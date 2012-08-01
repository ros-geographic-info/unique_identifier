cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)
rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# unit tests
rosbuild_add_boost_directories()
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
rosbuild_add_gtest(test_unique_id tests/test_unique_id.cpp)
rosbuild_add_pyunit(tests/test_unique_id.py)

