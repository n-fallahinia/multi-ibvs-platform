project(ibvs)
cmake_minimum_required(VERSION 3.0)

add_executable(ibvs main.cpp)

target_link_libraries(ibvs 
                        PRIVATE CameraClass
                        PRIVATE ImageClass
                        PRIVATE TrackingClass
                        PRIVATE MeasurementClass
                        PRIVATE RobotClass
                        )