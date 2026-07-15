cmake_minimum_required(VERSION 4.2)
project(count_walks_DAG)

set(CMAKE_CXX_STANDARD 23)

add_executable(count_walks_DAG
        main.cpp
        ../Graph/Graph.h
        ../Graph/Graph.cpp
)
