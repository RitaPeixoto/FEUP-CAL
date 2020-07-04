cmake_minimum_required(VERSION 3.15)
project(FichaJUNG)

set(CMAKE_CXX_STANDARD 14)
# The line below is necessary if you are under Windows only
# Comment the line below if you are under Linux or Mac OS
link_libraries(ws2_32 wsock32)

include_directories(lib)
include_directories(resources)
add_executable(FichaJUNG FichaJUNG.cpp lib/connection.cpp lib/graphviewer.cpp)
