cmake_minimum_required(VERSION 3.0)
project(Test)

add_library(Test
            src/TestClass.cpp
            src/TestClass.h)

target_include_directories(Test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src") 