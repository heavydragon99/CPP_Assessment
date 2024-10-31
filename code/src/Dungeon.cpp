#include "Dungeon.h"

#include "LocationFactory.h"
#include "EnemyFactory.h"
#include "GameObjectFactory.h"
#include "Enemy.h"
#include "RandomGenerator.h"
#include "Location.h"

#include <stdexcept>

// Dummy static Location for temporary initialization
static Location dummyLocation("dummy", "dummy", 0);

/**
 * @brief Constructor that takes a vector of ParsedLocations.
 *
 * @param aLocations A vector of parsed locations to initialize the dungeon.
 */
Dungeon::Dungeon(Sean::Vector<Sean::ParsedLocations> &aLocations)
    : mCurrentLocation(&dummyLocation) // Temporary initialization
{
    for (Sean::ParsedLocations &parsedLocation : aLocations)
    {
        try
        {
            // Create a new Location using the LocationFactory
            Sean::Object<Location> location(LocationFactory::createLocation(parsedLocation.mName.get(), parsedLocation.mDescription.get(), parsedLocation.mId));
            if (location.get() == nullptr)
            {
                throw std::runtime_error("Location not found");
            }

            // Add the new Location to mMap
            mMap.push_back(std::move(*location));

            // Add the enemies to the Location
            for (Sean::String &enemy : parsedLocation.mEnemies)
            {
                try
                {
                    Sean::Object<Enemy> newEnemy(EnemyFactory::createEnemy(enemy.get()));
                    if (newEnemy.get() == nullptr)
                    {
                        throw std::runtime_error("Enemy not found");
                    }
                    mMap.back().addEnemy(std::move(*newEnemy));
                }
                catch (const std::exception &e)
                {
                    throw;
                }
            }

            // Add the objects to the Location
            for (Sean::String &object : parsedLocation.mVisibleObjects)
            {
                try
                {
                    Sean::Object<GameObject> newObject(GameObjectFactory::createGameObject(object.get()));
                    if (newObject.get() == nullptr)
                    {
                        throw std::runtime_error("Object not found");
                    }
                    mMap.back().addVisibleObject(newObject.release());
                }
                catch (const std::exception &e)
                {
                    throw;
                }
            }

            for (Sean::String &object : parsedLocation.mHiddenObjects)
            {
                try
                {
                    Sean::Object<GameObject> newObject(GameObjectFactory::createGameObject(object.get()));
                    if (newObject.get() == nullptr)
                    {
                        throw std::runtime_error("Object not found");
                    }
                    mMap.back().addHiddenObject(newObject.release());
                }
                catch (const std::exception &e)
                {
                    throw;
                }
            }
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    // Second pass: Set the exits for each location
    for (Sean::ParsedLocations &parsedLocation : aLocations)
    {
        Location &currentLocation = mMap[parsedLocation.mId - 1];
        for (Sean::DirectionInfo &direction : parsedLocation.mDirections)
        {
            if (direction.mID > aLocations.size())
            {
                throw std::runtime_error("Invalid location ID");
            }
            if (direction.mID == 0)
            {
                break;
            }
            switch (direction.mDirection)
            {
            case Sean::Direction::North:
                currentLocation.setExit(Sean::Direction::North, &mMap[direction.mID - 1]);
                break;
            case Sean::Direction::East:
                currentLocation.setExit(Sean::Direction::East, &mMap[direction.mID - 1]);
                break;
            case Sean::Direction::South:
                currentLocation.setExit(Sean::Direction::South, &mMap[direction.mID - 1]);
                break;
            case Sean::Direction::West:
                currentLocation.setExit(Sean::Direction::West, &mMap[direction.mID - 1]);
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

/**
 * @brief Constructor that takes an integer representing the number of locations.
 *
 * @param aLocations The number of locations to generate in the dungeon.
 */
Dungeon::Dungeon(int aLocations)
    : mCurrentLocation(&dummyLocation) // Temporary initialization
{
    if (aLocations <= 0)
    {
        throw std::invalid_argument("Number of locations must be greater than zero");
    }

    RandomGenerator randomGen;
    Sean::Vector<Sean::String> usedNames;

    // Generate unique locations
    for (int i = 0; i < aLocations; ++i)
    {
        try
        {
            Sean::Object<Location> location;

            // Ensure unique location name
            do
            {
                location.reset(LocationFactory::createLocation());
            } while (usedNames.contains(location.get()->getName()));

            usedNames.push_back(location.get()->getName());
            mMap.push_back(std::move(*location));

            // Add visible objects
            int numVisibleObjects = randomGen.getRandomValue(0, 3);
            for (int j = 0; j < numVisibleObjects; ++j)
            {
                try
                {
                    Sean::Object<GameObject> object(GameObjectFactory::createGameObject());
                    if (object.get())
                    {
                        mMap.back().addVisibleObject(object.release());
                    }
                }
                catch (const std::exception &e)
                {
                    throw;
                }
            }

            // Add hidden objects
            int numHiddenObjects = randomGen.getRandomValue(0, 2);
            for (int j = 0; j < numHiddenObjects; ++j)
            {
                try
                {
                    Sean::Object<GameObject> object(GameObjectFactory::createGameObject());
                    if (object.get())
                    {
                        mMap.back().addHiddenObject(object.release());
                    }
                }
                catch (const std::exception &e)
                {
                    throw;
                }
            }
        }
        catch (const std::exception &e)
        {
            throw;
        }
    }

    // Ensure all locations are reachable by setting exits
    for (int i = 0; i < aLocations; ++i)
    {
        Location &currentLocation = mMap[i];
        int numExits = randomGen.getRandomValue(1, 4);
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
        try
        {
            Sean::Object<Enemy> enemy(EnemyFactory::createEnemy());
            if (enemy.get() != nullptr)
            {
                mMap[i % aLocations].addEnemy(*enemy);
            }
        }
        catch (const std::exception &e)
        {
            throw;
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

/**
 * @brief Copy constructor.
 *
 * @param other The other Dungeon to copy from.
 */
Dungeon::Dungeon(const Dungeon &other)
    : mMap(other.mMap), mCurrentLocation(other.mCurrentLocation)
{
}

/**
 * @brief Copy assignment operator.
 *
 * @param other The other Dungeon to copy from.
 * @return Dungeon& A reference to this object.
 */
Dungeon &Dungeon::operator=(const Dungeon &other)
{
    if (this != &other)
    {
        mMap = other.mMap;
        mCurrentLocation = other.mCurrentLocation;
    }
    return *this;
}

/**
 * @brief Updates the dungeon state.
 *
 * @return int The total damage taken from enemies.
 */
int Dungeon::update()
{
    int damage = 0;
    bool enemiesAlive = false;
    for (Enemy &enemy : mCurrentLocation->getEnemies())
    {
        if (!enemy.isDead())
        {
            enemiesAlive = true;
            int attack = enemy.getAttack();
            if (attack == 0)
            {
                std::cout << "De " << enemy.getName() << " mist je" << std::endl;
            }
            else
            {
                std::cout << "De " << enemy.getName() << " valt je aan met: " << attack << " schade" << std::endl;
            }

            damage += attack;
        }
    }
    if (!enemiesAlive)
    {
        moveEnemies();
    }

    return damage;
}

/**
 * @brief Creates a game object.
 *
 * @param aName The name of the game object to create.
 * @return GameObject* A pointer to the created game object.
 */
GameObject *Dungeon::createGameObject(const Sean::String &aName)
{
    return std::move(GameObjectFactory::createGameObject(aName));
}

/**
 * @brief Picks up an object from the current location.
 *
 * @param aObjectName The name of the object to pick up.
 * @return GameObject* A pointer to the picked-up object.
 */
GameObject *Dungeon::pickUpObject(const char *aObjectName)
{
    return mCurrentLocation->pickUpObject(aObjectName);
}

/**
 * @brief Places an object in the current location.
 *
 * @param aObject A pointer to the object to place.
 */
void Dungeon::placeObject(GameObject *aObject)
{
    mCurrentLocation->addVisibleObject(aObject);
}

/**
 * @brief Prints a short description of the current location.
 */
void Dungeon::printShortDescription() const
{
    mCurrentLocation->printDescriptionShort();
}

/**
 * @brief Prints a long description of the current location.
 */
void Dungeon::printLongDescription() const
{
    mCurrentLocation->printDescriptionLong();
    mCurrentLocation->printExits();
}

/**
 * @brief Checks if a location in the given direction is valid.
 *
 * @param aDirection The direction to check.
 * @return bool True if the location is valid, false otherwise.
 */
bool Dungeon::validLocation(Sean::Direction aDirection) const
{
    return mCurrentLocation->getExit(aDirection) != nullptr;
}

/**
 * @brief Moves to a new location in the given direction.
 *
 * @param aDirection The direction to move.
 * @return bool True if the move was successful, false otherwise.
 */
bool Dungeon::moveLocation(Sean::Direction aDirection)
{
    Location *newLocation = mCurrentLocation->getExit(aDirection);
    if (newLocation)
    {
        mCurrentLocation = newLocation;
        return true;
    }
    std::cout << "Er is geen locatie in die richting" << std::endl;
    return false;
}

/**
 * @brief Moves hidden objects in the current location.
 */
void Dungeon::moveHiddenObjects()
{
    mCurrentLocation->moveHiddenObjects();
}

/**
 * @brief Prints information about an object in the current location.
 *
 * @param aObjectName The name of the object to print.
 * @return bool True if the object was found, false otherwise.
 */
bool Dungeon::printObject(const char *aObjectName)
{
    return mCurrentLocation->printObject(aObjectName);
}

/**
 * @brief Teleports the player a certain number of locations.
 *
 * @param aAmount The number of locations to teleport.
 */
void Dungeon::teleport(int aAmount)
{
    if (aAmount >= mMap.size())
    {
        aAmount = mMap.size() - 1;
    }
    if (aAmount <= 0)
    {
        return;
    }

    Sean::Direction nextDirection = Sean::Direction::Invalid;
    Sean::Direction previousDirection = Sean::Direction::Invalid;
    RandomGenerator randomEngine;

    while (aAmount > 0)
    {
        Location *nextLocation = nullptr;
        Location *locationNorth = mCurrentLocation->getExit(Sean::Direction::North);
        Location *locationEast = mCurrentLocation->getExit(Sean::Direction::East);
        Location *locationSouth = mCurrentLocation->getExit(Sean::Direction::South);
        Location *locationWest = mCurrentLocation->getExit(Sean::Direction::West);

        int attempts = 0;
        const int maxAttempts = 20; // Maximum number of attempts to find a new direction

        do
        {
            nextDirection = static_cast<Sean::Direction>(randomEngine.getRandomValue(0, 3));
            switch (nextDirection)
            {
            case Sean::Direction::North:
                nextLocation = locationNorth;
                nextDirection = Sean::Direction::North;
                break;
            case Sean::Direction::East:
                nextLocation = locationEast;
                nextDirection = Sean::Direction::East;
                break;
            case Sean::Direction::South:
                nextLocation = locationSouth;
                nextDirection = Sean::Direction::South;
                break;
            case Sean::Direction::West:
                nextLocation = locationWest;
                nextDirection = Sean::Direction::West;
                break;
            }
            attempts++;
            if (attempts >= maxAttempts)
            {
                // Break out of the loop if max attempts are reached
                return;
            }
        } while (nextLocation == nullptr);

        if (nextDirection == previousDirection)
        {
            continue;
        }
        else
        {
            mCurrentLocation = nextLocation;
            previousDirection = nextDirection;
            --aAmount;
        }
    }
}

/**
 * @brief Attacks an enemy in the current location.
 *
 * @param aEnemyName The name of the enemy to attack.
 * @param aDamage The amount of damage to deal.
 * @return bool True if the enemy was found and attacked, false otherwise.
 */
bool Dungeon::attackEnemy(const char *aEnemyName, int aDamage)
{
    for (Enemy &enemy : mCurrentLocation->getEnemies())
    {
        if (enemy.getName() == aEnemyName)
        {
            if (!enemy.isDead())
            {
                enemy.takeDamage(aDamage);
                if (enemy.isDead())
                {
                    Sean::String enemyName = enemy.getName();
                    if (enemyName.starts_with("dode "))
                    {
                        enemyName = enemyName.substr(5);
                    }
                    std::cout << "Je hebt de " << enemyName << " " << aDamage << " schade toegediend en verslagen" << std::endl;
                }
                else
                {
                    std::cout << "Je hebt de " << enemy.getName() << " " << aDamage << " schade toegediend" << std::endl;
                }
                return true;
            }
            else
            {
                std::cout << "De " << enemy.getName() << " is al verslagen" << std::endl;
            }
        }
    }
    std::cout << "Er is geen vijand met de naam " << aEnemyName << std::endl;
    return false;
}

/**
 * @brief Gets the current location.
 *
 * @return const Location& A reference to the current location.
 */
const Location &Dungeon::getCurrentLocation() const
{
    return *mCurrentLocation;
}

/**
 * @brief Moves enemies in the dungeon.
 */
void Dungeon::moveEnemies()
{
    Sean::Vector<Sean::String> movedEnemies;
    RandomGenerator randomEngine;
    for (Location &location : mMap)
    {
        Sean::Vector<Location *> exits;
        Location *north = location.getExit(Sean::Direction::North);
        Location *east = location.getExit(Sean::Direction::East);
        Location *south = location.getExit(Sean::Direction::South);
        Location *west = location.getExit(Sean::Direction::West);
        if (north != nullptr)
        {
            exits.push_back(north);
        }
        if (east != nullptr)
        {
            exits.push_back(east);
        }
        if (south != nullptr)
        {
            exits.push_back(south);
        }
        if (west != nullptr)
        {
            exits.push_back(west);
        }

        Sean::Vector<Enemy> enemiesToMove;

        for (auto it = location.getEnemies().begin(); it != location.getEnemies().end(); ++it)
        {
            Enemy &enemy = *it;
            Sean::String enemyName = enemy.getName();
            if (movedEnemies.contains(enemyName) || enemy.isDead())
            {
                continue;
            }
            movedEnemies.push_back(enemyName);
            if (randomEngine.getChance(50) && !exits.empty())
            {
                enemiesToMove.push_back(enemy);
            }
        }

        // Move the enemies after collecting them
        for (Enemy &enemy : enemiesToMove)
        {
            Location *newLocation = exits[randomEngine.getRandomValue(0, exits.size() - 1)];
            newLocation->addEnemy(enemy);
            location.removeEnemy(enemy.getName().c_str());
        }
    }
}