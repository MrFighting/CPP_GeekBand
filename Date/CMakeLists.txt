cmake_minimum_required(VERSION 3.5)
project(Date)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Date.cpp Date.h)
add_executable(Date ${SOURCE_FILES})