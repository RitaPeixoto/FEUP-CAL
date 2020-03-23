cmake_minimum_required(VERSION 3.10)
project(CAL_FP04)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)



add_executable(CAL_FP04 main.cpp Tests/tests.cpp Tests/Graph.h Tests/Person.h Tests/Person.cpp)

target_link_libraries(CAL_FP04 gtest gtest_main)
