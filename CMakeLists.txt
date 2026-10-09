cmake_minimum_required(VERSION 3.10)

project(cpp_prac_dynamic_array CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(dynamic_array_demo
    src/main.cpp
    src/DynamicArray.cpp
)

target_include_directories(dynamic_array_demo PRIVATE include)