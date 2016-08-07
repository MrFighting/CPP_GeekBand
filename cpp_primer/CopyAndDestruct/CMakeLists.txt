cmake_minimum_required(VERSION 3.3)
project(CopyAndDestruct)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp HasPtr.cpp HasPtr.h)
add_executable(CopyAndDestruct ${SOURCE_FILES})