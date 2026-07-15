cmake_minimum_required(VERSION 4.1)
project(seminar3)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(Seminar3_Week1_stub/Seminar3_stub)

add_executable(seminar3
        Seminar3_Week1_stub/Seminar3_stub/Controller.cpp
        Seminar3_Week1_stub/Seminar3_stub/Controller.h
        Seminar3_Week1_stub/Seminar3_stub/DynamicVector.h
        Seminar3_Week1_stub/Seminar3_stub/main.cpp
        Seminar3_Week1_stub/Seminar3_stub/Repository.cpp
        Seminar3_Week1_stub/Seminar3_stub/Repository.h
        Seminar3_Week1_stub/Seminar3_stub/Song.cpp
        Seminar3_Week1_stub/Seminar3_stub/Song.h
        Seminar3_Week1_stub/Seminar3_stub/Tests.cpp
        Seminar3_Week1_stub/Seminar3_stub/Tests.h
        Seminar3_Week1_stub/Seminar3_stub/UI.cpp
        Seminar3_Week1_stub/Seminar3_stub/UI.h
        Seminar3_Week1_stub/Seminar3_stub/PlayList.cpp)
