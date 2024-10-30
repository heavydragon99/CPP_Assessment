cmake_minimum_required(VERSION 3.10)

# Set the project name
project(dungeon_crawler_tests)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find GoogleTest package
find_package(GTest REQUIRED)

# Include directories
# include_directories(${CMAKE_SOURCE_DIR}/inc)
# include_directories(${CMAKE_SOURCE_DIR}/external/sqlite3/inc)  # Include SQLite3 headers

# List all test source files
set(TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/tests/test_gameObjects.cpp
    ${CMAKE_SOURCE_DIR}/tests/test_sql.cpp
    ${CMAKE_SOURCE_DIR}/tests/test_xml.cpp
    ${CMAKE_SOURCE_DIR}/tests/tests.cpp
)

# Add the test executable
add_executable(${TESTS_NAME} ${TEST_SOURCES})

# Link GoogleTest libraries and the main library
target_link_libraries(${TESTS_NAME} PRIVATE ${GTEST_LIBRARIES} pthread tinyxml2 ${LIBRARY_NAME})

# Add custom target to run the tests
add_custom_target(run_tests
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TESTS_NAME}
    DEPENDS ${TESTS_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Running the tests"
)