cmake_minimum_required(VERSION 4.2)
project(matrix_multiplication)

set(CMAKE_CXX_STANDARD 23)

add_executable(matrix_multiplication
        main.cpp
        ../Graph/Graph.h
        ../Graph/Graph.cpp
)
