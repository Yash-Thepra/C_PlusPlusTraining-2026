cmake_minimum_required(VERSION 3.22.1)

project(MyAssignment)

set(CMAKE_CXX_STANDARD 17)

add_executable(result p1.cpp p2.cpp)

target_link_libraries(result gtest gtest_main pthread)