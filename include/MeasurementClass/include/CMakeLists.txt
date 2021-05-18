cmake_minimum_required(VERSION 3.0)
project(KalmanFilter)

add_library(KalmanFilter 
            src/kalman_filter.cpp
            src/kalman_filter.h)

target_include_directories(KalmanFilter PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src") 

message(STATUS "    Finished kalman @: ${CMAKE_CURRENT_SOURCE_DIR}")