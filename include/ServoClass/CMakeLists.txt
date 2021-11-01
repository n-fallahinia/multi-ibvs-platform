cmake_minimum_required(VERSION 3.0)
project(ServoClass)

set(ROBOT_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../RobotClass")


add_library(ServoClass 
            src/Servo.cpp
            src/Servo.h)

target_link_libraries(ServoClass
                    ${VISP_LIBRARIES} 
                    ${OpenCV_LIBS}
                        )

target_include_directories(ServoClass PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src") 

message(STATUS " Finished servo @: ${CMAKE_CURRENT_SOURCE_DIR}")