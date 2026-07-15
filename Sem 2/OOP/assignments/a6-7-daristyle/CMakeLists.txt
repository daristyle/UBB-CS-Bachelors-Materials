cmake_minimum_required(VERSION 4.1)
project(a6_7_daristyle)

set(CMAKE_CXX_STANDARD 23)

include_directories(src/Domain)
include_directories(src/Repository)
include_directories(src/Service)
include_directories(src/Tests)
include_directories(src/UI)
include_directories(src/Utilities)
include_directories(src/Validator)

find_package(SQLite3 REQUIRED)

add_executable(a6_7_daristyle
        src/Domain/Tutorial.cpp
        src/Domain/Tutorial.h
        src/Repository/MemoryRepository.cpp
        src/Repository/MemoryRepository.h
        src/Service/Service.cpp
        src/Service/Service.h
        src/Tests/Tests.cpp
        src/Tests/Tests.h
        src/UI/UI.cpp
        src/UI/UI.h
        src/Utilities/vector.h
        src/Utilities/vector.tpp
        src/main.cpp
        src/Repository/InterfaceRepository.h
        src/Repository/FileRepository.cpp
        src/Repository/FileRepository.h
        src/Repository/FileRepository.cpp
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
)

target_link_libraries(a6_7_daristyle PRIVATE SQLite::SQLite3)