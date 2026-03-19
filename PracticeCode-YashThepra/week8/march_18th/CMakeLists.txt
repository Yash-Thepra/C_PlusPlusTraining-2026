cmake_minimum_required(3.22.1)

project(practice)

set(CMAKE_CXX_STANDARD 17)

add_executable(result p2.cpp)

target_link_libraries(result gtest gtest_main pthread)