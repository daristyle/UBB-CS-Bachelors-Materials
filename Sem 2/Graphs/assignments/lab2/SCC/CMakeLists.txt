cmake_minimum_required(VERSION 4.2)
project(SCC)

set(CMAKE_CXX_STANDARD 23)

add_executable(SCC
        main.cpp
        ../Graph/Graph.h
        ../Graph/Graph.cpp
        ../Graph/IteratorRange.h
)
