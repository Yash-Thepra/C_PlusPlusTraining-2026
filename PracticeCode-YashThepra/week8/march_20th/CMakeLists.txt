cmake_minimum_required(VERSION 3.22.1)

project(AssignmentTests)

set(CMAKE_CXX_STANDARD 17)

add_executable(result p3.cpp p4.cpp)

target_link_libraries(result gtest gtest_main pthread)