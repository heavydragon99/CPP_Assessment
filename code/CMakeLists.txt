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
include_directories(external/sqlite3/inc)  # Include SQLite3 headers

# # Find all source files
# file(GLOB_RECURSE SOURCES "src/*.cpp" "external/sqlite3/src/*.c")  # Include SQLite3 source

# List all source files
set(SOURCES
    src/main.cpp
    external/sqlite3/src/sqlite3.c  # SQLite3 source file
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})