cmake_minimum_required(VERSION 3.8)
project(5)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c assignment.c assignment.h ex1.c ex2.c ex3.c ex4.c ex6.c)
add_executable(5 ${SOURCE_FILES})