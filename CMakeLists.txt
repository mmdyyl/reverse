cmake_minimum_required(VERSION 3.7)
project(reverse1)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-g -Wall")
set(SOURCE_FILES
        reverse/board.cpp
        reverse/board.h
        reverse/main.cpp
        reverse/player.cpp
        reverse/player.h
        reverse/Socket.cpp
        reverse/Socket.h reverse/playerbase.cpp reverse/playerbase.h reverse/game.cpp reverse/game.h reverse/human.cpp reverse/human.h)

add_executable(reverse1 ${SOURCE_FILES})
target_link_libraries(reverse1 ${GLUT_LIBRARY} ${OPENGL_LIBRARY})