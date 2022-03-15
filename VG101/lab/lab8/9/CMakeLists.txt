cmake_minimum_required(VERSION 3.8)
project(9)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp figures.cpp figures.h car.cpp car.h)
add_executable(9 ${SOURCE_FILES})
target_link_libraries(9 opengl32 glu32 freeglut)