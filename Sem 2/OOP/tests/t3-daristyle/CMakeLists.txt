cmake_minimum_required(VERSION 4.2)
project(t3_daristyle)

set(CMAKE_CXX_STANDARD 23)

include_directories(src/Repository)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(t3_daristyle
        src/Repository/Repository.cpp
        src/Repository/Repository.h
        src/Service/Service.cpp
        src/Service/Service.h
        src/UI/GUI.cpp
        src/UI/GUI.h
        src/UI/GUI.ui
        src/main.cpp
        src/Domain/Flight.cpp
        src/Domain/Flight.h
)

target_link_libraries(t3_daristyle PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)