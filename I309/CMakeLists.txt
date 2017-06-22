cmake_minimum_required(VERSION 3.7)
project(I309)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

set(SOURCE_FILES main.cpp)
add_executable(I309 ${SOURCE_FILES})
