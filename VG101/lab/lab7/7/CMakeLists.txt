cmake_minimum_required(VERSION 3.8)
project(7)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp figure.cpp figure.h)
add_executable(7 ${SOURCE_FILES})
target_link_libraries(7 opengl32 glu32 freeglut)