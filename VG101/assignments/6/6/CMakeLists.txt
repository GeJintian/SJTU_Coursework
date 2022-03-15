cmake_minimum_required(VERSION 3.8)
project(6)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c assignment.c assignment.h ex1.c ex2.c ex3.c ex4.c ex7.c list.c list.h ex5.c multiset.c multiset.h set.c set.h)
add_executable(6 ${SOURCE_FILES})