cmake_minimum_required(VERSION 3.10)

# Set the project name
project(dungeon_crawler_tests)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find GoogleTest package
find_package(GTest REQUIRED)

# Include common settings
include(${CMAKE_SOURCE_DIR}/common.cmake)

# List all test source files
set(TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/tests/test_sql.cpp
    ${CMAKE_SOURCE_DIR}/tests/tests.cpp
)

# Add the test executable
add_executable(${PROJECT_NAME} ${TEST_SOURCES} ${MAIN_SOURCES})

# Link GoogleTest libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTEST_LIBRARIES} pthread tinyxml2)

# Add custom target to run the tests
add_custom_target(run_tests
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Running the tests"
)