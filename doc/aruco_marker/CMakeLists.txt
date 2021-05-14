project(aruco_maker)
cmake_minimum_required(VERSION 2.8)

add_definitions(-std=c++11)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

find_package(VISP REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(aruco_maker main.cpp)
target_link_libraries(aruco_maker ${OpenCV_LIBS} )