cmake_minimum_required(VERSION 3.0)
project(SixGod)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread" )
set(CMAKE_CXX_STANDARD 14)

ADD_SUBDIRECTORY( include )
find_package(OpenCV QUIET)
message(${OpenCV_DIR})
if(${OpenCV_DIR} MATCHES "/usr/local/lib/cmake/opencv4")
    message("OpenCV Included.")
    include_directories(${OpenCV_INCLUDE_DIRS})
    SET(CMAKE_EXE_LINKER_FLAGS "-no-pie")
    ADD_COMPILE_OPTIONS(-fPIC)
    add_library(CAMERA camera.cpp camera.h)
    TARGET_LINK_LIBRARIES(CAMERA ${OpenCV_LIBS})
else()
    message(WARNING "OpenCV Not Included!!! Test Envrionment ONLY!!!")
    add_library(CAMERA camera.cpp camera.h)
endif()
add_library(LIDAR lidar.cpp lidar.h)

# Uncomment the following to apply the SPI Function.
#add_library(SPI spi.cpp spi.h)

add_library(UART uart.cpp uart.h)
TARGET_LINK_LIBRARIES(LIDAR RPLIDAR)

add_library(TRIAN Triangulation.cpp Triangulation.h)

add_library(MAP Map.cpp Map.h)

#Main Function
add_executable(SixGod main.cpp main.h)
TARGET_LINK_LIBRARIES(SixGod LIDAR CAMERA UART TRIAN MAP)

#Just Stop Everything ;-）
add_executable(Stop stop.cpp)
TARGET_LINK_LIBRARIES(Stop LIDAR CAMERA UART)

#Other Functions For Test.
#add_executable(Show show.cpp spi.cpp spi.h)
add_executable(Test test.cpp main.h)
TARGET_LINK_LIBRARIES(Test MAP TRIAN)