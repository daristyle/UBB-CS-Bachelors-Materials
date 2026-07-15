cmake_minimum_required(VERSION 4.2)
project(StarCatalogue3)

set(CMAKE_CXX_STANDARD 23)

include_directories(src/Domain)
include_directories(src/Repository)
include_directories(src/Service)
include_directories(src/UI)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(StarCatalogue3
        src/Domain/Astronomer.cpp
        src/Domain/Astronomer.h
        src/Domain/Star.cpp
        src/Domain/Star.h
        src/Repository/AstronomerRepository.cpp
        src/Repository/AstronomerRepository.h
        src/Repository/StarRepository.cpp
        src/Repository/StarRepository.h
        src/Service/Service.cpp
        src/Service/Service.h
        src/UI/GUI.cpp
        src/UI/GUI.h
        src/UI/GUI.ui
        src/UI/TableModel.cpp
        src/UI/TableModel.h
        src/main.cpp
)

target_link_libraries(StarCatalogue3 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)