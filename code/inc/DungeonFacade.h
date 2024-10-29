#ifndef DUNGEONFACADE_H
#define DUNGEONFACADE_H

#include "Dungeon.h"
#include "Sean.h"
#include "IGameObject.h"

#include <memory>

class DungeonFacade
{
public:
    // Constructors
    DungeonFacade() = default;

    // Destructor
    virtual ~DungeonFacade() = default;

    // Methods
    void createDungeon(std::vector<Sean::ParsedLocations> &aLocations);
    void generateDungeon(int aLocations);
    void printLongDescription() const;
    void printShortDescription() const;
    void moveHiddenObjects();
    IGameObject *pickUpObject(const char *aObjectName);
    bool placeObject(std::unique_ptr<IGameObject> aObject);
    bool printGameObject(const char *aObjectName) const;
    bool printEnemy(const char *aEnemyName) const;
    bool validLocation(Sean::Direction aDirection) const;
    bool moveLocation(Sean::Direction aDirection);
    bool attackEnemy(const char *aEnemyName, int aDamage);
    IGameObject *createGameObject(const Sean::String &aName);
    int update();
    void teleport(int aAmount);

private:
    // Private Methods

private:
    // Members
    std::unique_ptr<Dungeon> mDungeon;
};

#endif // DUNGEONFACADE_H