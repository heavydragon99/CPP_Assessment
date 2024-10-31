cmake_minimum_required(VERSION 3.10)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add an option to enable debug mode
option(ENABLE_DEBUG "Enable debug mode" OFF)

# Conditionally set build type and debug flags
if(ENABLE_DEBUG)
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
endif()

# Set the project name
project(dungeon_crawler)

# Set the library name
set(LIBRARY_NAME ${PROJECT_NAME}_lib)
set(TESTS_NAME ${PROJECT_NAME}_tests)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/inc)
include_directories(${CMAKE_SOURCE_DIR}/external/sqlite3/inc)  # Include SQLite3 headers

# List all main project source files excluding main.cpp
set(MAIN_SOURCES
    ${CMAKE_SOURCE_DIR}/src/ArmorObject.cpp
    ${CMAKE_SOURCE_DIR}/src/ConsumableObject.cpp
    ${CMAKE_SOURCE_DIR}/src/Dungeon.cpp
    ${CMAKE_SOURCE_DIR}/src/DungeonFacade.cpp
    ${CMAKE_SOURCE_DIR}/src/Enemy.cpp
    ${CMAKE_SOURCE_DIR}/src/EnemyFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/Game.cpp
    ${CMAKE_SOURCE_DIR}/src/GameObject.cpp
    ${CMAKE_SOURCE_DIR}/src/GameObjectFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/GoldObject.cpp
    ${CMAKE_SOURCE_DIR}/src/Location.cpp
    ${CMAKE_SOURCE_DIR}/src/LocationFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/Logger.cpp
    ${CMAKE_SOURCE_DIR}/src/Player.cpp
    ${CMAKE_SOURCE_DIR}/src/RandomGenerator.cpp
    ${CMAKE_SOURCE_DIR}/src/SqlReader.cpp
    ${CMAKE_SOURCE_DIR}/src/WeaponObject.cpp
    ${CMAKE_SOURCE_DIR}/src/XmlReader.cpp
    ${CMAKE_SOURCE_DIR}/external/sqlite3/src/sqlite3.c
)

# Add subdirectory
add_subdirectory(external/tinyxml2) # Include TinyXML2

# Create a library from the main sources
add_library(${LIBRARY_NAME} ${MAIN_SOURCES})

# Link libraries to library
target_link_libraries(${LIBRARY_NAME} tinyxml2)

# Add the executable
add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Link library
target_link_libraries(${PROJECT_NAME} ${LIBRARY_NAME})

# Add subdirectory for tests
add_subdirectory(tests)

# Add custom target to run Valgrind
add_custom_target(run_valgrind
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
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