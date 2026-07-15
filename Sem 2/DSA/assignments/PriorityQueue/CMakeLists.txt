cmake_minimum_required(VERSION 4.2)
project(PriorityQueue)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_executable(PriorityQueue
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        PriorityQueue.cpp
        PriorityQueue.h
        ShortTest.cpp
        ShortTest.h
)
