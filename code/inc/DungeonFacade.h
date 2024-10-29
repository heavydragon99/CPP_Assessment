#ifndef DUNGEONFACADE_H
#define DUNGEONFACADE_H

#include "Dungeon.h"
#include "Sean.h"
#include "IGameObject.h"

#include <memory>

class DungeonFacade
{
public:
    DungeonFacade() = default;
    virtual ~DungeonFacade() = default;

public:
    void createDungeon(std::vector<Sean::ParsedLocations> &aLocations);
    void generateDungeon(int aLocations);

    void printLongDescription();
    void printShortDescription();
    void moveHiddenObjects();
    IGameObject* pickUpObject(const char *aObjectName);
    bool placeObject(std::unique_ptr<IGameObject> aObject);
    bool printGameObject(const char *aObjectName);
    bool printEnemy(const char *aEnemyName);
    bool moveLocation(Sean::Direction aDirection);
    bool attackEnemy(const char *aEnemyName, int aDamage);
    IGameObject* createGameObject(const Sean::String &aName);
    int update();
    void teleport(int aAMount);

private:
    std::unique_ptr<Dungeon> mDungeon;
};

#endif // DUNGEONFACADE_H
