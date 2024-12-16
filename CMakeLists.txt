cmake_minimum_required(VERSION 3.29)
project(AdventOfCode2024)

set(CMAKE_CXX_STANDARD 20)

add_executable(AdventOfCode2024 16.cpp)

configure_file(${CMAKE_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/input.txt COPYONLY)
