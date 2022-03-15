cmake_minimum_required(VERSION 3.8)
project(3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp triangle.cpp triangle.h rectangle.cpp rectangle.h parallelogram.cpp parallelogram.h trapezium.cpp trapezium.h)
add_executable(3 ${SOURCE_FILES})