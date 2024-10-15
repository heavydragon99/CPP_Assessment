#ifndef GAMEOBJECTFACADE_H
#define GAMEOBJECTFACADE_H

#include "GameObject.h"

#include <memory>
#include <string>

class GameObjectFacade {
public:
    GameObjectFacade() = default;
    GameObjectFacade(GameObject &aGameObject);
    virtual ~GameObjectFacade() = default;

    std::string getName() const;
    void printName() const;
    void printDescription() const;
    ObjectType getType() const;

private:
     std::unique_ptr<GameObject> mGameObject;
};

#endif // GAMEOBJECTFACADE_H