#  =================================================================================
#     Image Class for handeling the image captured by the PointGrey cameras 
#     attached to each of the robots. Main objective of this class is to convert visp 
#     image in to the MAt format supported by opencv. Ultimatly, aruco tracking or YOLO 
#     will be used based of the converted images. 
# 
#     UNIVERSITY OF UTAH
#     BIOROBOTICS LAB
#     Navid Fallahinia
#     12/08/2019
# 
#     Copyright (c) 2019 Navid Fallahinia
# 
#     Permission is hereby granted, free of charge, to any person obtaining a copy
#     of this software and associated documentation files (the "Software"), to deal
#     in the Software without restriction, including without limitation the rights
#     to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#     copies of the Software, and to permit persons to whom the Software is
#     furnished to do so, subject to the following conditions:
# 
#     If you have questions regarding the use of this file, please contact
#     Biorobotics Lab at smascaro@utah.edu
# 
#    Description:
#    IBVS overall configuration file. Detect third party libraries 
# =================================================================================

project(IBVS C CXX)
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
# Modify default install prefix
if(WIN32)
    execute_process(COMMAND "${GIT_EXECUTABLE}" describe --tags --always --dirty --match "[0-9].[0-9].[0-9]*"
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()

# By default set release configuration
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

## add c++ definitions
add_definitions(-std=c++11)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

#-----------------------------------------------------------------------------
# IBVS version number.  An even minor number corresponds to releases.
set(IBVS_VERSION_MAJOR "1")
set(IBVS_VERSION_MINOR "1")
set(IBVS_VERSION_PATCH "3")
set(IBVS_VERSION "${VISP_VERSION_MAJOR}.${VISP_VERSION_MINOR}.${VISP_VERSION_PATCH}")
#-----------------------------------------------------------------------------

## set the executable to <install_directory>/bin
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
## set libraries (if any) to <install_directory>/bin
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
## set the module path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

## find the required packages 
find_package(VISP REQUIRED)
find_package(OpenCV REQUIRED)
if( "${OPENCV_VERSION}" LESS "4" )
    message( WARNING "OpenCV update is recommended !" )
elseif("${OPENCV_VERSION}" LESS "3")
    message( FATAL_ERROR "OpenCV version is not supported" )
endif()
###########################
# New packages go in here !
###########################

## set the flycapture directory 
set(FLYCAPTURE_INCLUDE_DIRS "/usr/include/flycapture")

## set the internal libraries in subdirectory 
set(CAMERACLASS_INCLUDE_DIRS "include/CameraClass")
set(IMAGERACLASS_INCLUDE_DIRS "include/ImageClass")
set(TRACKINGCLASS_INCLUDE_DIRS "include/TrackingClass")
###########################
# New libraries go in here !
###########################

message(STATUS "    include path: ${VISP_INCLUDE_DIRS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "    ==========================")
message(STATUS "    OpenCV version: ${OpenCV_VERSION}")
message(STATUS "    VISP version: ${VISP_VERSION}")
message(STATUS "    ==========================")

# include the the packages
include_directories(${VISP_INCLUDE_DIRS})
include_directories(${FLYCAPTURE_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

# OpenCV definition
add_definitions(${OpenCV_DEFINITIONS})

# include the libraries in subdirectory
add_subdirectory(${CAMERACLASS_INCLUDE_DIRS})
add_subdirectory(${IMAGERACLASS_INCLUDE_DIRS})
add_subdirectory(${TRACKINGCLASS_INCLUDE_DIRS})
###########################
# New includes go in here !
###########################

# include the the main directory
add_subdirectory(src)


