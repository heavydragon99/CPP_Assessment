#include "Dungeon.h"
#include "LocationFactory.h"
#include <stdexcept>

// Dummy static Location for temporary initialization
static Location dummyLocation("dummy", "dummy");

// Constructor that takes a vector of ParsedLocations
Dungeon::Dungeon(std::vector<Sean::ParsedLocations> &aLocations)
    : mCurrentLocation(&dummyLocation) // Temporary initialization
{
    for (auto &parsedLocation : aLocations)
    {
        // Create a new Location using the LocationFactory
        Sean::Object<Location> location(LocationFactory::createLocation(parsedLocation.mName.get(), parsedLocation.mDescription.get())); 
        // Add the new Location to mMap
        mMap.push_back(location.get());
    }

    // Set mCurrentLocation to the first location in the map if available
    if (!mMap.empty())
    {
        mCurrentLocation = mMap[0];
    }
    else
    {
        throw std::runtime_error("No locations provided");
    }
}

// Constructor that takes an integer
Dungeon::Dungeon(int aLocations)
    : mCurrentLocation(&dummyLocation) // Temporary initialization
{
    throw std::runtime_error("Function not implemented");
}

// Copy constructor
Dungeon::Dungeon(const Dungeon& other)
    : mCurrentLocation(&dummyLocation) // Temporary initialization
{
    for (auto location : other.mMap)
    {
        Location *newLocation = new Location(*location);
        mMap.push_back(newLocation);
    }

    if (!mMap.empty())
    {
        mCurrentLocation = mMap[0];
    }
}

// Copy assignment operator
Dungeon& Dungeon::operator=(const Dungeon& other)
{
    if (this == &other) return *this; // Self-assignment check

    // Release existing resources
    for (auto location : mMap)
    {
        delete location;
    }
    mMap.clear();

    // Copy new resources
    for (auto location : other.mMap)
    {
        Location *newLocation = new Location(*location);
        mMap.push_back(newLocation);
    }

    if (!mMap.empty())
    {
        mCurrentLocation = mMap[0];
    }
    else
    {
        mCurrentLocation = &dummyLocation;
    }

    return *this;
}

// Destructor
Dungeon::~Dungeon()
{
    for (auto location : mMap)
    {
        delete location;
    }
}