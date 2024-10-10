#ifndef LOCATION_H
#define LOCATION_H

#include "Sean.h"
#include "GameObject.h"
#include "Enemy.h"

#define MAX_EXITS 4

class Location {
public:
    Location(const char* aName, const char* aDescription);
    virtual ~Location();

    void setName(const char* aName);
    void setDescription(const char* aDescription);
    void addVisibleObject(GameObject aObject);
    void addHiddenObject(GameObject aObject);
    void addEnemy(Enemy aEnemy);

    void printDescriptionShort() const;
    void printDescriptionLong() const;
    void update();


private:
    Sean::CharArray mName; // Name of the location
    Sean::CharArray mDescription; // Description of the location
    Sean::Vector<GameObject> mVisibleObjects; // Objects that are visible in the location
    Sean::Vector<GameObject> mHiddenObjects; // Objects that are hidden in the location
    Sean::Vector<Enemy> mEnemies; // Enemies in the location
    //Location& mExits[MAX_EXITS]; // TODO
};

#endif // LOCATION_H