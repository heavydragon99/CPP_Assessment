#ifndef LOCATION_H
#define LOCATION_H

#include "Sean.h"
#include "GameObject.h"
#include "Enemy.h"

#define MAX_EXITS 4

class Location {
public:
    Location() = default;
    virtual ~Location() = default;

    void setName(const char* aName);
    void setDescription(const char* aDescription);
    void addVisibleObject(Sean::UniquePtr<GameObject> aObject);
    void addHiddenObject(Sean::UniquePtr<GameObject> aObject);
    void addEnemy(Sean::UniquePtr<Enemy> aEnemy);

    void printDescriptionShort();
    void printDescriptionLong();
    void update();


private:
    Sean::CharArray mName; // Name of the location
    Sean::CharArray mDescription; // Description of the location
    Sean::Vector<Sean::UniquePtr<GameObject>> mVisibleObjects; // Objects that are visible in the location
    Sean::Vector<Sean::UniquePtr<GameObject>> mHiddenObjects; // Objects that are hidden in the location
    Sean::Vector<Sean::UniquePtr<Enemy>> mEnemies; // Enemies in the location
    //Location& mExits[MAX_EXITS]; // TODO
};

#endif // LOCATION_H