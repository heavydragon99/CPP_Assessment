#ifndef LOCATION_H
#define LOCATION_H

#include "Sean.h"
#include "GameObject.h"
#include "Enemy.h"

class Location
{
public:
    Location() = default;
    Location(const Sean::String aName, const Sean::String aDescription, int aID);
    virtual ~Location() = default;

    Sean::String getName() const;

    void addVisibleObject(GameObject aObject);
    void addHiddenObject(GameObject aObject);
    void addEnemy(Enemy aEnemy);
    void setExit(Sean::Direction aDirection, Location *aLocation);
    Location *getExit(Sean::Direction aDirection) const;

    void printDescriptionShort() const;
    void printDescriptionLong() const;
    void printExits() const;
    void update();

private:
    Sean::String mName;                       // Name of the location
    int mID;                                  // ID of the location
    Sean::String mDescription;                // Description of the location
    Sean::Vector<GameObject> mVisibleObjects; // Objects that are visible in the location
    Sean::Vector<GameObject> mHiddenObjects;  // Objects that are hidden in the location
    Sean::Vector<Enemy> mEnemies;             // Enemies in the location

    Location *mNorth;
    Location *mEast;
    Location *mSouth;
    Location *mWest;
};

#endif // LOCATION_H