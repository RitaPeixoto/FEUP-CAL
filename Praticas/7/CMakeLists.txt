cmake_minimum_required(VERSION 3.10)
project(CAL_FP07)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)



add_executable(CAL_FP07 main.cpp Tests/tests.cpp Tests/Graph.h Tests/MutablePriorityQueue.h)

target_link_libraries(CAL_FP07 gtest gtest_main)
