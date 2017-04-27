cmake_minimum_required(VERSION 3.7)
project(reverse1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        reverse/board.cpp
        reverse/board.h
        reverse/main.cpp
        reverse/player.cpp
        reverse/player.h
        reverse/Socket.cpp
        reverse/Socket.h reverse/playerbase.cpp reverse/playerbase.h reverse/game.cpp reverse/game.h reverse/human.cpp reverse/human.h)

add_executable(reverse1 ${SOURCE_FILES})