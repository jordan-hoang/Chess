cmake_minimum_required(VERSION 3.13)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chess main.cpp libs/Piece.cpp libs/Piece.h termcolor.hpp libs/Board.cpp libs/Board.h)