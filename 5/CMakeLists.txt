cmake_minimum_required(VERSION 3.10)
project(CAL_FP05)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)



add_executable(CAL_FP05 main.cpp Tests/tests.cpp Tests/Graph.h Tests/MutablePriorityQueue.h)

target_link_libraries(CAL_FP05 gtest gtest_main)
