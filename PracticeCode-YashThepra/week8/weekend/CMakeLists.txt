cmake_minimum_required(VERSION 3.22.1)

project(AssignmentTests)

set(CMAKE_CXX_STANDARD 17)

add_executable(result p2.cpp)

find_package(GTest REQUIRED)

target_link_libraries(result
    GTest::gtest
    GTest::gtest_main
    GTest::gmock
)