cmake_minimum_required(VERSION 3.8)
project(1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp figures.cpp figures.h machine.cpp machine.h)
add_executable(1 ${SOURCE_FILES})
target_link_libraries(1 opengl32 glu32 freeglut)