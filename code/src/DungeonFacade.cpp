#include "DungeonFacade.h"
#include <stdexcept>

void DungeonFacade::createDungeon(std::vector<Sean::ParsedLocations> &aLocations)
{
    if (mDungeon == nullptr)
    {
        mDungeon = std::make_unique<Dungeon>(aLocations);
        
    }
    else
    {
        throw std::runtime_error("Dungeon already created");
    }
}

void DungeonFacade::generateDungeon(int aLocations)
{
    if (mDungeon == nullptr)
    {
        mDungeon = std::make_unique<Dungeon>(aLocations);
    }
    else
    {
        throw std::runtime_error("Dungeon already created");
    }
}

void DungeonFacade::printLongDescription()
{
    throw std::runtime_error("Function not implemented");
}

void DungeonFacade::printShortDescription()
{
    throw std::runtime_error("Function not implemented");
}

void DungeonFacade::moveHiddenObjects()
{
    throw std::runtime_error("Function not implemented");
}

GameObjectFacade* DungeonFacade::pickUpObject(const char *aObjectName)
{
    throw std::runtime_error("Function not implemented");
}

bool DungeonFacade::placeObject(GameObjectFacade* aObject)
{
    throw std::runtime_error("Function not implemented");
}

bool DungeonFacade::printGameObject(const char *aObjectName)
{
    throw std::runtime_error("Function not implemented");
}

bool DungeonFacade::printEnemy(const char *aEnemyName)
{
    throw std::runtime_error("Function not implemented");
}

bool DungeonFacade::moveLocation(Sean::Direction aDirection)
{
    throw std::runtime_error("Function not implemented");
}

bool DungeonFacade::attackEnemy(const char *aEnemyName, GameObjectFacade &aWeapon)
{
    throw std::runtime_error("Function not implemented");
}

GameObject* DungeonFacade::getGameObject(const Sean::String &aName)
{
    return std::move(mDungeon->getGameObject(aName));
}