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

# Include common settings
include(${CMAKE_SOURCE_DIR}/common.cmake)

# Add subdirectory
add_subdirectory(external/tinyxml2) # Include TinyXML2

# Add the executable
add_executable(${PROJECT_NAME} ${MAIN_SOURCES} ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Link library
target_link_libraries(${PROJECT_NAME} tinyxml2)

# Add subdirectory for tests
add_subdirectory(tests)

# Add custom target to run Valgrind
add_custom_target(run_valgrind
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Running Valgrind to check for memory leaks"
)

# Add custom target to run the main program
add_custom_target(run
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Running the main program"
)