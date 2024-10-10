#ifndef DUNGEON_H
#define DUNGEON_H

#include "Sean.h"
#include "Location.h"

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

private:
    std::vector<Location> mMap;
    Location *mCurrentLocation;
};

#endif // DUNGEON_H