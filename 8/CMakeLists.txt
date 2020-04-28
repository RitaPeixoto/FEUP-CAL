cmake_minimum_required(VERSION 3.10)
project(CAL_FP08)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)



add_executable(CAL_FP08 main.cpp Tests/tests.cpp Tests/Graph.h)

target_link_libraries(CAL_FP08 gtest gtest_main)
