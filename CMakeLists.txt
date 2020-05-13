project(ibvs)
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
## add c++ definitions
add_definitions(-std=c++11)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

## Install the executable to <install_directory>/bin
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
## Install libraries (if any) to <install_directory>/bin
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

## find the required packages 
find_package(VISP REQUIRED)
find_package(OpenCV REQUIRED)
###########################
# New packages go in here !
###########################

## set the flycapture directory 
set(FLYCAPTURE_INCLUDE_DIRS "/usr/include/flycapture")

## set the internal libraries in subdirectory 
set(CAMERACLASS_INCLUDE_DIRS "include/CameraClass")
set(IMAGERACLASS_INCLUDE_DIRS "include/ImageClass")
###########################
# New libraries go in here !
###########################

# message(STATUS "    include path: ${VISP_INCLUDE_DIRS}")
# message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
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
###########################
# New includes go in here !
###########################

# include the the main directory
add_subdirectory(src)


