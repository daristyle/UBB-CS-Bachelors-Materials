cmake_minimum_required(VERSION 4.2)
project(BCC)

set(CMAKE_CXX_STANDARD 23)

add_executable(BCC
        main.cpp
        ../Graph/Graph.h
        ../Graph/Graph.cpp
)
