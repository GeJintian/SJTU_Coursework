cmake_minimum_required(VERSION 3.8)
project(2)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c sum.c sum.h prod.c prod.h quorem.c quorem.h exp.c exp.h sum.c sum.h prod.c prod.h)
add_executable(2 ${SOURCE_FILES})