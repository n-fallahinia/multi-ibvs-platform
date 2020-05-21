cmake_minimum_required(VERSION 3.0)
project(TrackingClass)

add_library(TrackingClass 
            src/Tracking.cpp
            src/Tracking.h)

target_link_libraries(TrackingClass # TBD+++++++++++++++++++
                        ${OpenCV_LIBS})
                    
target_include_directories(TrackingClass PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src") 