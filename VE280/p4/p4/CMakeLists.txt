cmake_minimum_required(VERSION 3.12)
project(p4)

set(CMAKE_CXX_STANDARD 14)

add_executable(p4 game.cpp
        board.h
        exceptions.cpp
        exceptions.h
        piece.h
        player.h
        pool.h
        quarto.cpp
        quarto.h
        square.h piece.cpp pool.cpp board.cpp square.cpp player.cpp)

add_executable(te test.cpp
        board.h
        exceptions.cpp
        exceptions.h
        piece.h
        player.h
        pool.h
        quarto.cpp
        quarto.h
        square.h piece.cpp pool.cpp board.cpp square.cpp player.cpp)