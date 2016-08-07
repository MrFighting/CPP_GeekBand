cmake_minimum_required(VERSION 3.3)
project(StrVec_Ch13)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp StrVec.cpp StrVec.h )
add_executable(StrVec_Ch13 ${SOURCE_FILES})