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
    mDungeon->printLongDescription();
}

void DungeonFacade::printShortDescription()
{
    throw std::runtime_error("Function not implemented");
}

void DungeonFacade::moveHiddenObjects()
{
    throw std::runtime_error("Function not implemented");
}

GameObjectFacade *DungeonFacade::pickUpObject(const char *aObjectName)
{
    throw std::runtime_error("Function not implemented");
}

bool DungeonFacade::placeObject(std::unique_ptr<GameObjectFacade> aObject)
{
    mDungeon->placeObject(aObject->getGameObject());
    return true;
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
    return mDungeon->moveLocation(aDirection);
}

bool DungeonFacade::attackEnemy(const char *aEnemyName, GameObjectFacade &aWeapon)
{
    throw std::runtime_error("Function not implemented");
}

GameObject *DungeonFacade::getGameObject(const Sean::String &aName)
{
    return std::move(mDungeon->getGameObject(aName));
}

void DungeonFacade::update()
{
    mDungeon->update();
}