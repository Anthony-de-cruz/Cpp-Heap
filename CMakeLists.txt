cmake_minimum_required(VERSION 3.20.0)
project(Cpp-Heap)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb")
add_executable(Cpp-Heap example/basic_example.cpp)
