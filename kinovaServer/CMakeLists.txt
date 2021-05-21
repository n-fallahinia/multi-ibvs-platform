cmake_minimum_required(VERSION 2.8)
project(kinova_server_test)
# project(test)

# find_package(X11 REQUIRED)
# message(STATUS "X11_FOUND = ${X11_FOUND}")
# message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
# message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

# include_directories(${X11_INCLUDE_DIR})
# link_directories(${X11_LIBRARIES})

add_executable(kinova_server_test robots_server.cxx)
# add_executable(test test.cxx)
# target_link_libraries(tcpip_test ${X11_LIBRARIES})