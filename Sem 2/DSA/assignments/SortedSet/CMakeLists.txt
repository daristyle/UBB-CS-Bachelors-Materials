cmake_minimum_required(VERSION 4.2)
project(SortedSet)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_executable(SortedSet
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SortedSet.cpp
        SortedSet.h
        SortedSetIterator.cpp
        SortedSetIterator.h)
