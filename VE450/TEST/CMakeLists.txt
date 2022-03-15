cmake_minimum_required(VERSION 3.12)
project(TEST)

set(CMAKE_CXX_STANDARD 14)

add_executable(TEST main.cpp Triangluation.cpp Triangluation.h Map.cpp Map.h main.h)