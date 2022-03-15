cmake_minimum_required(VERSION 3.12)
project(5)

set(CMAKE_CXX_STANDARD 14)

add_executable(5 main.cpp priority_queue.h unsorted_heap.h fib_heap.h binary_heap.h game.cpp game.h)
add_executable(test test_heap.cpp priority_queue.h unsorted_heap.h game.h)
add_executable(xby main.cpp priority_queue.h game.cpp game.h xby.h)
add_executable(opt opt.cpp)
add_executable(performance performance.cpp priority_queue.h unsorted_heap.h fib_heap.h binary_heap.h game.cpp game.h)
add_executable(xby_test xby_test.cpp priority_queue.h unsorted_heap.h fib_heap.h binary_heap.h)