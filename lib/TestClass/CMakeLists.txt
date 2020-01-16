project(testclass)
cmake_minimum_required(VERSION 2.8)
# find_package(VISP REQUIRED)
# find_package(OpenCV REQUIRED)

add_library(TestClass 
            src/TestClass.cpp
            src/TestClass.h)
