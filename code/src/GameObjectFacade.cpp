#include "GameObjectFacade.h"

GameObjectFacade::GameObjectFacade(GameObject &aGameObject)
    : mGameObject(&aGameObject)
{
}

GameObjectFacade::GameObjectFacade(std::unique_ptr<GameObject> aGameObject)
    : mGameObject(std::move(aGameObject))
{
}

GameObject *GameObjectFacade::getGameObject()
{
    return mGameObject.get();
}

std::string GameObjectFacade::getName() const
{
    return mGameObject->getName().c_str();
}

void GameObjectFacade::printName() const
{
    mGameObject->printName();
}

void GameObjectFacade::printDescription() const
{
    mGameObject->printDescription();
}

ObjectType GameObjectFacade::getType() const
{
    return mGameObject->getType();
}