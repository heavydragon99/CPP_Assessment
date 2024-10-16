#include "Dungeon.h"

#include "LocationFactory.h"
#include "EnemyFactory.h"
#include "GameObjectFactory.h"
#include "Enemy.h"

#include <stdexcept>
#include <unordered_set>
#include <random>

// Dummy static Location for temporary initialization
static Location dummyLocation("dummy", "dummy", 0);

// Constructor that takes a vector of ParsedLocations
Dungeon::Dungeon(std::vector<Sean::ParsedLocations> &aLocations)
    : mCurrentLocation(&dummyLocation) // Temporary initialization
{
    for (Sean::ParsedLocations &parsedLocation : aLocations)
    {
        // Create a new Location using the LocationFactory
        Sean::Object<Location> location(LocationFactory::createLocation(parsedLocation.mName.get(), parsedLocation.mDescription.get(), parsedLocation.mId));
        if (location.get() == nullptr)
        {
            throw std::runtime_error("Location not found");
        }

        // Add the new Location to mMap
        mMap.push_back(*location.get());

        // Add the enemies to the Location
        for (Sean::String &enemy : parsedLocation.mEnemies)
        {
            Sean::Object<Enemy> newEnemy(EnemyFactory::createEnemy(enemy.get()));
            if (newEnemy.get() == nullptr)
            {
                throw std::runtime_error("Enemy not found");
            }
            mMap.back().addEnemy(*newEnemy.get());
        }

        // Add the objects to the Location
        for (Sean::String &object : parsedLocation.mVisibleObjects)
        {
            Sean::Object<GameObject> newObject(GameObjectFactory::createGameObject(object.get()));
            if (newObject.get() == nullptr)
            {
                throw std::runtime_error("Object not found");
            }
            mMap.back().addVisibleObject(*newObject.get());
        }

        for (Sean::String &object : parsedLocation.mHiddenObjects)
        {
            Sean::Object<GameObject> newObject(GameObjectFactory::createGameObject(object.get()));
            if (newObject.get() == nullptr)
            {
                throw std::runtime_error("Object not found");
            }
            mMap.back().addHiddenObject(*newObject.get());
        }
    }

    // Second pass: Set the exits for each location
    for (Sean::ParsedLocations &parsedLocation : aLocations)
    {
        Location &currentLocation = mMap[parsedLocation.mId-1];
        for (Sean::DirectionInfo &direction : parsedLocation.mDirections)
        {
            if(direction.mID > aLocations.size()){
                throw std::runtime_error("Invalid location ID");
            }
            if(direction.mID == 0){
                break;
            }
            switch (direction.mDirection)
            {
            case Sean::Direction::North:
                currentLocation.setExit(Sean::Direction::North, &mMap[direction.mID-1]);
                break;
            case Sean::Direction::East:
                currentLocation.setExit(Sean::Direction::East, &mMap[direction.mID-1]);
                break;
            case Sean::Direction::South:
                currentLocation.setExit(Sean::Direction::South, &mMap[direction.mID-1]);
                break;
            case Sean::Direction::West:
                currentLocation.setExit(Sean::Direction::West, &mMap[direction.mID-1]);
                break;
            }
        }
    }

    // Set mCurrentLocation to the first location in the map if available
    if (!mMap.empty())
    {
        mCurrentLocation = &mMap[0];
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
    if (aLocations <= 0)
    {
        throw std::invalid_argument("Number of locations must be greater than zero");
    }

    std::unordered_set<std::string> usedNames;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> visibleDist(0, 3);
    std::uniform_int_distribution<> hiddenDist(0, 2);
    std::uniform_int_distribution<> exitDist(1, 4);

    // Generate unique locations
    for (int i = 0; i < aLocations; ++i)
    {
        Sean::Object<Location> location;
        do
        {
            location.reset(LocationFactory::createLocation());
        } while (usedNames.find(location.get()->getName().c_str()) != usedNames.end());

        usedNames.insert(location.get()->getName().c_str());
        mMap.push_back(*location.get());

        // Add visible objects
        int numVisibleObjects = visibleDist(gen);
        for (int j = 0; j < numVisibleObjects; ++j)
        {
            GameObject *object = GameObjectFactory::createGameObject();
            if (object)
            {
                mMap.back().addVisibleObject(*object);
            }
        }

        // Add hidden objects
        int numHiddenObjects = hiddenDist(gen);
        for (int j = 0; j < numHiddenObjects; ++j)
        {
            GameObject *object = GameObjectFactory::createGameObject();
            if (object)
            {
                mMap.back().addHiddenObject(*object);
            }
        }
    }

    // Ensure all locations are reachable by setting exits
    for (int i = 0; i < aLocations; ++i)
    {
        Location &currentLocation = mMap[i];
        int numExits = exitDist(gen);
        for (int j = 0; j < numExits; ++j)
        {
            int exitIndex = (i + j + 1) % aLocations;
            currentLocation.setExit(static_cast<Sean::Direction>(j % 4), &mMap[exitIndex]);
        }
    }

    // Add enemies to the dungeon
    int numEnemies = (aLocations + 2) / 3; // One enemy per 3 locations, rounded up
    for (int i = 0; i < numEnemies; ++i)
    {
        Enemy *enemy = EnemyFactory::createEnemy();
        if (enemy)
        {
            mMap[i % aLocations].addEnemy(*enemy);
        }
    }

    // Set mCurrentLocation to the first location in the map if available
    if (!mMap.empty())
    {
        mCurrentLocation = &mMap[0];
    }
    else
    {
        throw std::runtime_error("No locations provided");
    }
}

void Dungeon::update(){
    throw std::runtime_error("Not implemented");
}

GameObject* Dungeon::getGameObject(const Sean::String &aName){
    return std::move(GameObjectFactory::createGameObject(aName)); 
}

void Dungeon::placeObject(GameObject *aObject){
    mCurrentLocation->addVisibleObject(*aObject);
}

void Dungeon::printShortDescription() const{
    mCurrentLocation->printDescriptionShort();
}

void Dungeon::printLongDescription() const{
    mCurrentLocation->printDescriptionLong();
    mCurrentLocation->printExits();
}