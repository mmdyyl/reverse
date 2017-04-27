cmake_minimum_required(VERSION 3.7)
project(reverse)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        reverse/board.cpp
        reverse/board.h
        reverse/main.cpp
        reverse/player.cpp
        reverse/player.h
        reverse/Socket.cpp
        reverse/Socket.h)

add_executable(reverse ${SOURCE_FILES})