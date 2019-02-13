cmake_minimum_required(VERSION 3.13)
project(Chess)



set(CMAKE_CXX_STANDARD 17)

add_executable(Chess main.cpp libs/src/Piece.cpp libs/header/Piece.h termcolor.hpp libs/src/Board.cpp libs/header/Board.h libs/src/MoveValidator.cpp libs/header/MoveValidator.h)