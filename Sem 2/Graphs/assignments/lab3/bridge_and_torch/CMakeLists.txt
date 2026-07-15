cmake_minimum_required(VERSION 4.2)
project(bridge_and_torch)

set(CMAKE_CXX_STANDARD 23)

add_executable(bridge_and_torch
        main.cpp
        ../Graph/Graph.h
        ../Graph/Graph.cpp
)
