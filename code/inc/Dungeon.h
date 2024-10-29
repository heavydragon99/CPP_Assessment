#ifndef DUNGEON_H
#define DUNGEON_H

#include "Sean.h"
#include "Location.h"
#include "WeaponObject.h"

#include <vector>

class Dungeon
{
public:
    Dungeon(std::vector<Sean::ParsedLocations> &aLocations);
    Dungeon(int aLocations);
    Dungeon(const Dungeon& other); // Copy constructor
    Dungeon& operator=(const Dungeon& other); // Copy assignment operator
    Dungeon(Dungeon&& other) = delete; // Move constructor
    Dungeon& operator=(Dungeon&& other) = delete; // Move assignment operator
    virtual ~Dungeon() = default;

    public:
    int update();
    GameObject* createGameObject(const Sean::String &aName);
    GameObject* pickUpObject(const char *aObjectName);
    void placeObject(GameObject *aObject);
    void printShortDescription() const;
    void printLongDescription() const;
    bool moveLocation(Sean::Direction aDirection);
    void moveHiddenObjects();
    bool printObject(const char *aObjectName);
    void teleport(int aAmount);
    bool attackEnemy(const char *aEnemyName, int aDamage);

    private:
    void moveEnemies();

private:
    Sean::Vector<Location> mMap; //unordered_map would be way better!!!!!!!!!!
    Location *mCurrentLocation;
};

#endif // DUNGEON_H