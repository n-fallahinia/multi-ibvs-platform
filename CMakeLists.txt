project(ibvs)
cmake_minimum_required(VERSION 3.0)


add_executable(ibvs src/main.cpp)

add_subdirectory(lib/TestClass)
target_link_libraries(ibvs TestClass)

