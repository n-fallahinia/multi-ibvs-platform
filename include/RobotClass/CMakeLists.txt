cmake_minimum_required(VERSION 3.0)
project(RobotClass)

add_library(RobotClass 
            src/Robot.cpp
            src/Robot.h)

target_link_libraries(RobotClass
                    ServoClass)

target_include_directories(RobotClass PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src") 

message(STATUS " Finished robot @: ${CMAKE_CURRENT_SOURCE_DIR}")