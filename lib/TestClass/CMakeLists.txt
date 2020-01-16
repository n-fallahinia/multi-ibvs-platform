cmake_minimum_required(VERSION 3.0)
project(TestClass)

add_library(TestClass 
            src/TestClass.cpp
            src/TestClass.h)

target_include_directories(TestClass PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src") 