cmake_minimum_required(VERSION 4.2)
project(minimum_cost_walks)

set(CMAKE_CXX_STANDARD 23)

add_executable(minimum_cost_walks
        main.cpp
        ../Graph/Graph.h
        ../Graph/Graph.cpp
)
