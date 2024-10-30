#include "DungeonFacade.h"
#include <stdexcept>

/**
 * @brief Creates a dungeon with the given parsed locations.
 * 
 * @param aLocations A vector of parsed locations to initialize the dungeon.
 * @throws std::runtime_error if the dungeon is already created.
 */
void DungeonFacade::createDungeon(std::vector<Sean::ParsedLocations> &aLocations)
{
    if (mDungeon == nullptr)
    {
        Sean::Vector<Sean::ParsedLocations> locations;
        for (Sean::ParsedLocations &parsedLocation : aLocations)
        {
            locations.push_back(parsedLocation);
        }
        mDungeon = std::make_unique<Dungeon>(locations);
    }
    else
    {
        throw std::runtime_error("Dungeon already created");
    }
}

/**
 * @brief Generates a dungeon with a specified number of locations.
 * 
 * @param aLocations The number of locations to generate in the dungeon.
 * @throws std::runtime_error if the dungeon is already created or if an invalid argument is provided.
 */
void DungeonFacade::generateDungeon(int aLocations)
{
    if (mDungeon == nullptr)
    {
        try {
            mDungeon = std::make_unique<Dungeon>(aLocations);
        } catch (const std::invalid_argument &e) {
            throw std::runtime_error(e.what());
        }
    }
    else
    {
        throw std::runtime_error("Dungeon already created");
    }
}

/**
 * @brief Prints a long description of the current location in the dungeon.
 */
void DungeonFacade::printLongDescription() const
{
    mDungeon->printLongDescription();
}

/**
 * @brief Prints a short description of the current location in the dungeon.
 */
void DungeonFacade::printShortDescription() const
{
    mDungeon->printShortDescription();
}

/**
 * @brief Moves hidden objects in the current location.
 */
void DungeonFacade::moveHiddenObjects()
{
    mDungeon->moveHiddenObjects();
}

/**
 * @brief Picks up an object from the current location.
 * 
 * @param aObjectName The name of the object to pick up.
 * @return IGameObject* A pointer to the picked-up object.
 */
IGameObject *DungeonFacade::pickUpObject(const char *aObjectName)
{
    return mDungeon->pickUpObject(aObjectName);
}

/**
 * @brief Places an object in the current location.
 * 
 * @param aObject A unique pointer to the object to place.
 * @return bool True if the object was placed successfully, false otherwise.
 * @throws std::runtime_error if the object type is invalid.
 */
bool DungeonFacade::placeObject(std::unique_ptr<IGameObject> aObject)
{
    // Convert IGameObject to GameObject
    Sean::Object<GameObject> gameObject(dynamic_cast<GameObject *>(aObject.release()));
    if (gameObject.get() != nullptr)
    {
        mDungeon->placeObject(gameObject.release());
        return true;
    }
    throw std::runtime_error("Invalid object type");
}

/**
 * @brief Prints information about a game object in the current location.
 * 
 * @param aObjectName The name of the object to print.
 * @return bool True if the object was found, false otherwise.
 */
bool DungeonFacade::printGameObject(const char *aObjectName) const
{
    return mDungeon->printObject(aObjectName);
}

/**
 * @brief Prints information about an enemy in the current location.
 * 
 * @param aEnemyName The name of the enemy to print.
 * @return bool True if the enemy was found, false otherwise.
 * @throws std::runtime_error as the function is not implemented.
 */
bool DungeonFacade::printEnemy(const char *aEnemyName) const
{
    throw std::runtime_error("Function not implemented");
}

/**
 * @brief Checks if a location in the given direction is valid.
 * 
 * @param aDirection The direction to check.
 * @return bool True if the location is valid, false otherwise.
 */
bool DungeonFacade::validLocation(Sean::Direction aDirection) const
{
    return mDungeon->validLocation(aDirection);
}

/**
 * @brief Moves to a new location in the given direction.
 * 
 * @param aDirection The direction to move.
 * @return bool True if the move was successful, false otherwise.
 */
bool DungeonFacade::moveLocation(Sean::Direction aDirection)
{
    return mDungeon->moveLocation(aDirection);
}

/**
 * @brief Attacks an enemy in the current location.
 * 
 * @param aEnemyName The name of the enemy to attack.
 * @param aDamage The amount of damage to deal.
 * @return bool True if the enemy was found and attacked, false otherwise.
 */
bool DungeonFacade::attackEnemy(const char *aEnemyName, int aDamage)
{
    return mDungeon->attackEnemy(aEnemyName, aDamage);
}

/**
 * @brief Creates a game object.
 * 
 * @param aName The name of the game object to create.
 * @return IGameObject* A pointer to the created game object.
 */
IGameObject *DungeonFacade::createGameObject(const Sean::String &aName)
{
    return std::move(mDungeon->createGameObject(aName));
}

/**
 * @brief Updates the dungeon state.
 * 
 * @return int The total damage taken from enemies.
 */
int DungeonFacade::update()
{
    return mDungeon->update();
}

/**
 * @brief Teleports the player a certain number of locations.
 * 
 * @param aAmount The number of locations to teleport.
 */
void DungeonFacade::teleport(int aAmount)
{
    mDungeon->teleport(aAmount);
}