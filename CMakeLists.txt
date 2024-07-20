cmake_minimum_required(VERSION 3.20.0)

project(Cpp-Heap
    DESCRIPTION "A heap implementation in C++"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)

# Update the submodules here
include(cmake/update_submodules.cmake)

add_subdirectory(external)
add_subdirectory(tests)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(Cpp-Heap 
    example/basic_example.cpp
    src/heap.cpp
)

target_include_directories(Cpp-Heap PRIVATE ${PROJECT_SOURCE_DIR}/src)
