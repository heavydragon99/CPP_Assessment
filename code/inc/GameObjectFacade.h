#ifndef GAMEOBJECTFACADE_H
#define GAMEOBJECTFACADE_H

#include "GameObject.h"

#include <memory>
#include <string>

class GameObjectFacade
{
public:
    GameObjectFacade() = default;
    GameObjectFacade(GameObject &aGameObject);
    GameObjectFacade(std::unique_ptr<GameObject> aGameObject);
    virtual ~GameObjectFacade() = default;

    // Delete copy constructor and copy assignment operator
    GameObjectFacade(const GameObjectFacade &) = delete;
    GameObjectFacade &operator=(const GameObjectFacade &) = delete;

    // Allow move constructor and move assignment operator
    GameObjectFacade(GameObjectFacade &&) = default;
    GameObjectFacade &operator=(GameObjectFacade &&) = default;

    GameObject *getGameObject();
    std::string getName() const;
    void printName() const;
    void printDescription() const;
    ObjectType getType() const;

private:
    std::unique_ptr<GameObject> mGameObject;
};

#endif // GAMEOBJECTFACADE_H