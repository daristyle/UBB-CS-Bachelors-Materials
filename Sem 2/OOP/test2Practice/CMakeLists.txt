cmake_minimum_required(VERSION 4.2)
project(test2Practice)

set(CMAKE_CXX_STANDARD 23)

include_directories(src/Domain)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(test2Practice
        src/Domain/Bill.cpp
        src/Domain/Bill.h
        src/Repository/Repository.cpp
        src/Repository/Repository.h
        src/Service/Service.cpp
        src/Service/Service.h
        src/UI/GUI.cpp
        src/UI/GUI.h
        src/UI/GUI.ui
        src/main.cpp
)

target_link_libraries(test2Practice PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)