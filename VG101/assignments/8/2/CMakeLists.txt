cmake_minimum_required(VERSION 3.8)
project(2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp parkinglot.cpp parkinglot.h figure.cpp figure.h)
add_executable(2 ${SOURCE_FILES})
target_link_libraries(2 opengl32 glu32 freeglut)