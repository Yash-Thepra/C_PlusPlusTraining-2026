find_package(GTest REQUIRED)

file(GLOB_RECURSE PROJECT_SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

list(FILTER PROJECT_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

file(GLOB_RECURSE TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(
    UnitTests
    ${PROJECT_SOURCES}
    ${TEST_SOURCES}
)

target_include_directories(
    UnitTests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks
)

target_link_libraries(
    UnitTests
    PRIVATE
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
        GTest::gmock_main
        pthread
)

include(GoogleTest)

gtest_discover_tests(UnitTests)