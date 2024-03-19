cmake_minimum_required(VERSION 3.29.0)
project(GRAPH_LAB)

set(CMAKE_CXX_STANDARD 17)
include_directories("include/")

add_executable(main
    ../source/main.cpp
    ../source/create_image.cpp
    ../source/draw_graph.cpp
    ../source/graph_algo.cpp
    ../source/make_tests.cpp
    ../source/math.cpp
)