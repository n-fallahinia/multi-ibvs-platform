cmake_minimum_required(VERSION 3.0)
project(CameraClass)

add_library(CameraClass 
            src/Camera.cpp
            src/Camera.h)

target_include_directories(CameraClass PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src") 
target_link_libraries(CameraClass ${VISP_LIBRARIES})
target_link_libraries(CameraClass ${OpenCV_LIBS} )