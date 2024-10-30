#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include "GameObject.h"
#include "Sean.h"

/**
 * @brief Factory class for creating GameObject objects.
 */
class GameObjectFactory
{
public:
    // Constructors
    GameObjectFactory() = default;

    // Destructor
    virtual ~GameObjectFactory() = default;

    // Methods
    static GameObject *createGameObject(const Sean::String &aName);
    static GameObject *createGameObject();

    static void resetCounter();

private:
    // Private Methods
    static void incrementCounter();

private:
    // Members
    /**
     * @brief Counter for assigning unique IDs to game objects.
     */
    static int mCounter;
};

#endif // GAMEOBJECTFACTORY_H