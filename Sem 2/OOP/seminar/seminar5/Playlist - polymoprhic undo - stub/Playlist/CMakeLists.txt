cmake_minimum_required(VERSION 4.2)
project(Playlist)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_executable(Playlist
        CSVPlaylist.cpp
        CSVPlaylist.h
        FilePlaylist.cpp
        FilePlaylist.h
        main.cpp
        PlayList.cpp
        PlayList.h
        Repository.cpp
        Repository.h
        RepositoryExceptions.cpp
        RepositoryExceptions.h
        Service.cpp
        Service.h
        Song.cpp
        Song.h
        SongValidator.cpp
        SongValidator.h
        UI.cpp
        UI.h
        Utils.cpp
        Utils.h
        Action.h
        ActionAdd.cpp
        ActionAdd.h
        ActionRemove.cpp
        ActionRemove.h
        ActionUpdate.cpp
        ActionUpdate.h
        Utils.tpp)
