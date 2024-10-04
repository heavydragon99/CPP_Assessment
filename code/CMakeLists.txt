cmake_minimum_required(VERSION 3.10)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set the project name
project(dungeon_crawler)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(inc)

# Find all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})