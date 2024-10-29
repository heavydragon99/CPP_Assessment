#ifndef LOCATION_H
#define LOCATION_H

#include "Sean.h"
#include "GameObject.h"
#include "Enemy.h"

class Location
{
public:
    // Constructors
    Location() = default;
    Location(const Sean::String aName, const Sean::String aDescription, int aID);

    // Destructor
    virtual ~Location() = default;

    // Assignment Operators
    Location(const Location &) = default;
    Location &operator=(const Location &) = default;
    Location(Location &&) noexcept = default;
    Location &operator=(Location &&) noexcept = default;

    // Methods
    Sean::String getName() const;
    void addVisibleObject(GameObject *aObject);
    void addHiddenObject(GameObject *aObject);
    void addEnemy(Enemy aEnemy);
    void removeEnemy(const char *aEnemyName);
    void setExit(Sean::Direction aDirection, Location *aLocation);
    Location *getExit(Sean::Direction aDirection) const;
    Sean::Vector<Enemy> &getEnemies();
    void printDescriptionShort() const;
    void printDescriptionLong() const;
    void printExits() const;
    void moveHiddenObjects();
    GameObject *pickUpObject(const char *aObjectName);
    bool printObject(const char *aObjectName);

private:
    // Private Methods

public:
    // Members

private:
    // Members
    Sean::String mName;                                     // Name of the location
    int mID;                                                // ID of the location
    Sean::String mDescription;                              // Description of the location
    Sean::Vector<Sean::Object<GameObject>> mVisibleObjects; // Objects that are visible in the location
    Sean::Vector<Sean::Object<GameObject>> mHiddenObjects;  // Objects that are hidden in the location
    Sean::Vector<Enemy> mEnemies;                           // Enemies in the location
    Location *mNorth;
    Location *mEast;
    Location *mSouth;
    Location *mWest;
};

#endif // LOCATION_H