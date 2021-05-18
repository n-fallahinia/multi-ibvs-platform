cmake_minimum_required(VERSION 3.0)
project(MeasurementClass)

set(KALMNCLASS_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")
add_subdirectory(${KALMNCLASS_INCLUDE_DIRS})

add_library(MeasurementClass 
            src/Measurement.cpp
            src/Measurement.h)

target_link_libraries(MeasurementClass
                        KalmanFilter)

target_include_directories(MeasurementClass PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src") 

message(STATUS "    Finished measurment @: ${CMAKE_CURRENT_SOURCE_DIR}")