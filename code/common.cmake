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
    ${CMAKE_SOURCE_DIR}/src/GameObjectFacade.cpp
    ${CMAKE_SOURCE_DIR}/src/GameObjectFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/GoldObject.cpp
    ${CMAKE_SOURCE_DIR}/src/Location.cpp
    ${CMAKE_SOURCE_DIR}/src/LocationFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/Player.cpp
    ${CMAKE_SOURCE_DIR}/src/SqlReader.cpp
    ${CMAKE_SOURCE_DIR}/src/WeaponObject.cpp
    ${CMAKE_SOURCE_DIR}/src/XmlReader.cpp
    ${CMAKE_SOURCE_DIR}/external/sqlite3/src/sqlite3.c
)