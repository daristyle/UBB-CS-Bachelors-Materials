cmake_minimum_required(VERSION 4.1)
project(cannibals_and_missionairs)

set(CMAKE_CXX_STANDARD 23)

add_executable(cannibals_and_missionairs
        main.cpp
        ../Graph/Graph.h
        ../Graph/Graph.cpp
)