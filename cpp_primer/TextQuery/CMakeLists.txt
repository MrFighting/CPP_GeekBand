cmake_minimum_required(VERSION 3.3)
project(TextQuery)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp TextBuider.cpp TextBuider.h QueryResult.cpp QueryResult.h)
add_executable(TextQuery ${SOURCE_FILES})