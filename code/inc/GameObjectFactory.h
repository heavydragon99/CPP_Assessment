#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include "GameObject.h"

class GameObjectFactory
{
public:
    GameObjectFactory() = default;
    virtual ~GameObjectFactory() = default;

    static GameObject *createGameObject(const Sean::String aName);
    static GameObject *createGameObject();

    private:
    static int mCounter;
};

#endif // GAMEOBJECTFACTORY_H