cmake_minimum_required(VERSION 3.10)

# Set the project name
project(dungeon_crawler_tests)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the CMAKE_MODULE_PATH to include the directory containing FindGMock.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Find GoogleTest and GoogleMock packages
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

# List all test source files
set(TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/tests/test_enemy.cpp
    ${CMAKE_SOURCE_DIR}/tests/test_gameObjects.cpp
    ${CMAKE_SOURCE_DIR}/tests/test_gameObjectsFactory.cpp
    ${CMAKE_SOURCE_DIR}/tests/test_player.cpp
    ${CMAKE_SOURCE_DIR}/tests/test_sql.cpp
    ${CMAKE_SOURCE_DIR}/tests/test_xml.cpp
    ${CMAKE_SOURCE_DIR}/tests/tests.cpp
)

# Add the test executable
add_executable(${PROJECT_NAME} ${TEST_SOURCES})

# Link GoogleTest, GoogleMock libraries and the main library
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::GTest GMock::GMock pthread ${LIBRARY_NAME})

# Add custom target to run the tests
add_custom_target(run_tests
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Running the tests"
)