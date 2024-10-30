#ifndef DUNGEON_H
#define DUNGEON_H

#include "Sean.h"
#include "Location.h"
#include "WeaponObject.h"

/**
 * @class Dungeon
 * @brief A class representing a dungeon in the game.
 * 
 * This class manages the locations, objects, and enemies within a dungeon.
 */
class Dungeon
{
public:
    // Constructors
    Dungeon(std::vector<Sean::ParsedLocations> &aLocations);
    Dungeon(int aLocations);
    Dungeon(const Dungeon& other); // Copy constructor
    Dungeon& operator=(const Dungeon& other); // Copy assignment operator
    Dungeon(Dungeon&& other) = delete; // Move constructor
    Dungeon& operator=(Dungeon&& other) = delete; // Move assignment operator

    // Destructor
    virtual ~Dungeon() = default;

    // Methods
    int update();
    GameObject* createGameObject(const Sean::String &aName);
    GameObject* pickUpObject(const char *aObjectName);
    void placeObject(GameObject *aObject);
    void printShortDescription() const;
    void printLongDescription() const;
    bool validLocation(Sean::Direction aDirection) const;
    bool moveLocation(Sean::Direction aDirection);
    void moveHiddenObjects();
    bool printObject(const char *aObjectName);
    void teleport(int aAmount);
    bool attackEnemy(const char *aEnemyName, int aDamage);
    const Location& getCurrentLocation() const;

private:
    // Private Methods
    void moveEnemies();

private:
    /**
     * @brief The map of the dungeon, containing all locations.
     */
    Sean::Vector<Location> mMap; //unordered_map would be way better!!!!!!!!!!

    /**
     * @brief The current location of the player in the dungeon.
     */
    Location *mCurrentLocation;
};

#endif // DUNGEON_H