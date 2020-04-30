project(ibvs)
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

add_definitions(-std=c++11)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

## Install the executable to <install_directory>/bin
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
## Install libraries (if any) to <install_directory>/bin
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

find_package(VISP REQUIRED)
find_package(OpenCV REQUIRED)
# set the flycapture directory 
set(FLYCAPTURE_INCLUDE_DIRS "/usr/include/flycapture")

# message(STATUS "    include path: ${VISP_INCLUDE_DIRS}")
# message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

message(STATUS "    ==========================")
message(STATUS "    OpenCV version: ${OpenCV_VERSION}")
message(STATUS "    VISP version: ${VISP_VERSION}")
message(STATUS "    ==========================")

include_directories(${VISP_INCLUDE_DIRS})
include_directories(${FLYCAPTURE_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(include/CameraClass)
add_subdirectory(src)
# add_definitions(${OpenCV_DEFINITIONS})


