cmake_minimum_required(VERSION 3.0)
project(ImageClass)

add_library(ImageClass 
            src/Image.cpp
            src/Image.h)

target_link_libraries(ImageClass # TBD+++++++++++++++++++
                        ${VISP_LIBRARIES} 
                        ${OpenCV_LIBS})
                    
target_include_directories(ImageClass PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src") 
