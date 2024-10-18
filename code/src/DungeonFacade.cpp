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
    mDungeon->printShortDescription();
}

void DungeonFacade::moveHiddenObjects()
{
    mDungeon->moveHiddenObjects();
}

IGameObject *DungeonFacade::pickUpObject(const char *aObjectName)
{
    return mDungeon->pickUpObject(aObjectName);
}

bool DungeonFacade::placeObject(std::unique_ptr<IGameObject> aObject)
{
        // Convert IGameObject to GameObject
    Sean::Object<GameObject> gameObject(dynamic_cast<GameObject*>(aObject.release()));
    if (gameObject.get() != nullptr)
    {
        mDungeon->placeObject(gameObject.get());
        return true;
    }
    throw std::runtime_error("Invalid object type");
}

bool DungeonFacade::printGameObject(const char *aObjectName)
{
    return mDungeon->printObject(aObjectName);
}

bool DungeonFacade::printEnemy(const char *aEnemyName)
{
    throw std::runtime_error("Function not implemented");
}

bool DungeonFacade::moveLocation(Sean::Direction aDirection)
{
    return mDungeon->moveLocation(aDirection);
}

bool DungeonFacade::attackEnemy(const char *aEnemyName, IGameObject &aWeapon)
{
    throw std::runtime_error("Function not implemented");
}

IGameObject *DungeonFacade::createGameObject(const Sean::String &aName)
{
    return std::move(mDungeon->createGameObject(aName));
}

void DungeonFacade::update()
{
    mDungeon->update();
}