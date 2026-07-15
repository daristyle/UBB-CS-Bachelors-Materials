cmake_minimum_required(VERSION 4.2)
project(HeldKarpDP)

set(CMAKE_CXX_STANDARD 23)

add_executable(HeldKarpDP
        main.cpp
        ../Graph/Graph.h
        ../Graph/Graph.cpp
)