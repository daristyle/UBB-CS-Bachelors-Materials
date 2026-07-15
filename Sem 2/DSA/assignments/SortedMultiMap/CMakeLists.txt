cmake_minimum_required(VERSION 4.2)
project(SortedMultiMap)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_executable(SortedMultiMap
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SMMIterator.cpp
        SMMIterator.h
        SortedMultiMap.cpp
        SortedMultiMap.h
        Utilities/dynamicarray.h
)
