cmake_minimum_required(VERSION 3.8)
project(exam2)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c assignment.c assignment.h ex3.c ex2.c ex1.c)
add_executable(exam2 ${SOURCE_FILES})