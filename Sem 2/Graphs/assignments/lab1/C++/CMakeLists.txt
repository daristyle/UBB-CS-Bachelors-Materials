cmake_minimum_required(VERSION 4.1)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(lab1
        Graph.cpp
        Graph.h
        main.cpp
        IteratorRange.tpp
        IteratorRange.h)
