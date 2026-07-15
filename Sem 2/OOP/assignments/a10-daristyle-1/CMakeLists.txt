cmake_minimum_required(VERSION 3.20)
project(a10_daristyle_1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(src/Domain)
include_directories(src/Repository)
include_directories(src/Service)
include_directories(src/Tests)
include_directories(src/UI)
include_directories(src/Utilities)
include_directories(src/Validator)

find_package(SQLite3 REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets WebEngineWidgets Charts)

add_executable(a10_daristyle_1
        src/Domain/Tutorial.cpp
        src/Domain/Tutorial.h
        src/Domain/Operation.h
        src/Repository/MemoryRepository.cpp
        src/Repository/MemoryRepository.h
        src/Service/Service.cpp
        src/Service/Service.h
        src/Tests/Tests.cpp
        src/Tests/Tests.h
        src/UI/CUI.cpp
        src/UI/CUI.h
        src/Utilities/vector.h
        src/main.cpp
        src/Repository/InterfaceRepository.h
        src/Repository/FileRepository.cpp
        src/Repository/FileRepository.h
        src/Repository/TextFileRepository.cpp
        src/Repository/TextFileRepository.h
        src/Validator/TutorialValidator.cpp
        src/Validator/TutorialValidator.h
        src/Repository/SQLiteRepository.cpp
        src/Repository/SQLiteRepository.h
        src/Repository/HTMLFileRepository.cpp
        src/Repository/HTMLFileRepository.h
        src/Repository/CSVFileRepository.cpp
        src/Repository/CSVFileRepository.h
        src/UI/UI.h
        src/UI/GUI.cpp
        src/UI/GUI.h
        src/UI/UI.cpp
        src/UI/GUI2.cpp
        src/UI/GUI2.h
        src/Domain/OperationAdd.cpp
        src/Domain/OperationAdd.h
        src/Domain/OperationRemove.cpp
        src/Domain/OperationRemove.h
        src/Domain/OperationUpdate.cpp
        src/Domain/OperationUpdate.h
        src/UI/TutorialTabelModel.cpp
        src/UI/TutorialTabelModel.h
)

target_link_libraries(a10_daristyle_1 PRIVATE SQLite::SQLite3)
target_link_libraries(a10_daristyle_1 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::WebEngineWidgets Qt6::Charts)