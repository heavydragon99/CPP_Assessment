cmake_minimum_required(VERSION 3.10)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Add debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Set the project name
project(dungeon_crawler)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(inc)
include_directories(external/sqlite3/inc)  # Include SQLite3 headers

# Add subdirectory
add_subdirectory(external/tinyxml2) # Include TinyXML2

# Find all source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "external/sqlite3/src/*.c")  # Include SQLite3 source

# Exclude specific files
list(REMOVE_ITEM SOURCES
    ${CMAKE_SOURCE_DIR}/external/sqlite3/src/shell.c
)


# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link library
target_link_libraries(${PROJECT_NAME} tinyxml2)