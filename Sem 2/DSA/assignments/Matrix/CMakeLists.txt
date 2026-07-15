cmake_minimum_required(VERSION 4.2)
project(Matrix)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_executable(Matrix
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        Matrix.cpp
        Matrix.h
        ShortTest.cpp
        ShortTest.h
)
