cmake_minimum_required(VERSION 3.7)
project(I309)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Cell.cpp Cell.h)
add_executable(I309 ${SOURCE_FILES})
