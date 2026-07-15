cmake_minimum_required(VERSION 4.1)
project(test1Practice)

set(CMAKE_CXX_STANDARD 20)

include_directories(src/Domain)

add_executable(test1Practice
        src/Domain/Car.cpp
        src/Domain/Car.h
        src/Repository/Repository.cpp
        src/Repository/Repository.h
        src/Service/Service.cpp
        src/Service/Service.h
        src/UI/UI.cpp
        src/UI/UI.h
        src/main.cpp)
