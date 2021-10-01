cmake_minimum_required(VERSION 2.8)
project(ibvs_sim)

## find the required packages 
find_package(VISP REQUIRED)
include_directories(${VISP_INCLUDE_DIRS})
add_executable(ibvs_sim sim.cpp)

target_link_libraries(ibvs_sim ${VISP_LIBRARIES})
