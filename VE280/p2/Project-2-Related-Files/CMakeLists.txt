cmake_minimum_required(VERSION 3.12)
project(Project_2_Related_Files)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project_2_Related_Files
        p2.h
        p2.cpp
        recursive.cpp
        recursive.h
        test_wyx.cpp
        )