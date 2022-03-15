cmake_minimum_required(VERSION 3.12)
project(cpppy)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-lpython)

include_directories(C:\\Users\\69009\\Anaconda3\\include)
link_libraries(C:/Users/69009/Anaconda3/libs/python37.lib)
link_directories(C:/Users/69009/Anaconda3/libs)

add_executable(cpppy main.cpp)
find_package(PythonLibs)
target_link_libraries(cpppy "C:/Users/69009/Anaconda3/Lib/site-packages")


set(Python3_ROOT_DIR C:/Users/69009/Anaconda3)
find_package(Python3 3.7 COMPONENTS Interpreter Development)
if (Python3_FOUND)
    message("Python include directory: " ${Python3_INCLUDE_DIRS})
    message("Python version is: " ${Python3_VERSION})
    include_directories(${Python3_INCLUDE_DIRS})
    target_link_libraries(cpppy ${Python3_LIBRARIES})
endif (Python3_FOUND)