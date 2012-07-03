cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

rosbuild_init()

# build messages
rosbuild_genmsg()

# unit tests
rosbuild_add_pyunit(tests/test_unique_id.py)

