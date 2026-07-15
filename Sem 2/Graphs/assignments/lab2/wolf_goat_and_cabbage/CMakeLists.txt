cmake_minimum_required(VERSION 4.1)
project(wolf_goat_and_cabbage)

set(CMAKE_CXX_STANDARD 23)

add_executable(wolf_goat_and_cabbage
        main.cpp
        ../Graph/Graph.h
        ../Graph/Graph.cpp
)