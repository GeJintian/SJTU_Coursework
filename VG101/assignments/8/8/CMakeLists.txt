cmake_minimum_required(VERSION 3.8)
project(8)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp assignment.cpp assignment.h ex1.cpp ex2.cpp Car.cpp Car.h figures.cpp figures.h parkinglot.cpp parkinglot.h)
add_executable(8 ${SOURCE_FILES})
target_link_libraries(8 opengl32 glu32 freeglut)