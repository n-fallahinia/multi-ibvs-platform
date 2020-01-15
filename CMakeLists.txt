project(ibvs)
cmake_minimum_required(VERSION 2.8)
# find_package(VISP REQUIRED)
# find_package(OpenCV REQUIRED)

add_library(testlib 
            TestClass.cpp
            TestClass.h)

add_executable(ibvs main.cpp)
target_link_libraries(ibvs PRIVATE testlib)

