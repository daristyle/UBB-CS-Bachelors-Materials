cmake_minimum_required(VERSION 4.2)
project(practicalexam_911_912_daristyle)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)
include_directories(Domain)
include_directories(Repository)
include_directories(Service)
include_directories(UI)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(practicalexam_911_912_daristyle
        src/main.cpp
        src/Domain/Researcher.cpp
        src/Domain/Researcher.h
        src/Domain/Idea.cpp
        src/Domain/Idea.h
        src/Repository/IdeaRepository.cpp
        src/Repository/IdeaRepository.h
        src/Repository/ResercherRepository.cpp
        src/Repository/ResercherRepository.h
        src/Service/Service.cpp
        src/Service/Service.h
        src/UI/TabelModel.cpp
        src/UI/TabelModel.h
        src/UI/GUI.cpp
        src/UI/GUI.h
        src/UI/GUI.ui
        src/UI/DeveloperGUI.cpp
        src/UI/DeveloperGUI.h
        src/UI/DeveloperGUI.ui
)

target_link_libraries(practicalexam_911_912_daristyle PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)