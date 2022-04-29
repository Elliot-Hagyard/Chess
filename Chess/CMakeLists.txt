cmake_minimum_required(VERSION 3.20)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled1 main.cpp Pieces.h Definitions.h Game.h Board.h Game.cpp Board.cpp)
