cmake_minimum_required(VERSION 3.15)
project(tourmateapp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

link_libraries(ws2_32 wsock32)

include_directories(lib)
add_executable(tourmateapp lib/connection.cpp lib/graphviewer.cpp
        main.cpp
        Graph/Stop.h
        Graph/MutablePriorityQueue.h
        Graph/Graph.cpp Graph/Graph.h
        POIGraph/POIEdge.h POIGraph/POIVertex.h POIGraph/POIGraph.h
        UserInteraction/ClientInfo.cpp UserInteraction/ClientInfo.h
        Utils/Util.cpp Utils/Util.h
        UserInteraction/InterestManager.cpp UserInteraction/InterestManager.h
        UserInteraction/MagicGenerator.cpp UserInteraction/MagicGenerator.h
        Utils/ReadFiles.cpp Utils/ReadFiles.h
        UserInteraction/AlgorithmAnalysis.cpp UserInteraction/AlgorithmAnalysis.h
        UserInteraction/Menu.cpp UserInteraction/Menu.h
        Utils/GraphView.cpp Utils/GraphView.h)