project(ibvs)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

## Install the executable to <install_directory>/bin
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
## Install libraries (if any) to <install_directory>/bin
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_subdirectory(include/TestClass)
add_subdirectory(src)


