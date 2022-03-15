cmake_minimum_required(VERSION 3.8)
project(2)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c mean.c mean.h median.c median.h variance.c variance.h deviation.c deviation.h)
add_executable(2 ${SOURCE_FILES})