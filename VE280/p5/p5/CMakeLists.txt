cmake_minimum_required(VERSION 3.12)
project(p5)

set(CMAKE_CXX_STANDARD 14)

add_executable(p5 main.cpp
        dlist.h dlist_impl.h calc.cpp)

add_executable(try 123.cpp
        dlist.h dlist_impl.h)

add_executable(call call.cpp
        dlist.h dlist_impl.h)