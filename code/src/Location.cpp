#include "Location.h"
#include <iostream>

/**
 * @brief Constructs a new Location object.
 * 
 * @param aName The name of the location.
 * @param aDescription The description of the location.
 * @param aID The ID of the location.
 */
Location::Location(const Sean::String aName, const Sean::String aDescription, int aID)
    : mName(aName), mDescription(aDescription), mNorth(nullptr), mEast(nullptr), mSouth(nullptr), mWest(nullptr), mID(aID)
{
}

/**
 * @brief Gets the name of the location.
 * 
 * @return The name of the location.
 */
Sean::String Location::getName() const
{
    return mName + std::to_string(mID).c_str();
}

/**
 * @brief Adds a visible object to the location.
 * 
 * @param aObject The object to add.
 */
void Location::addVisibleObject(GameObject *aObject)
{
    mVisibleObjects.push_back(Sean::Object<GameObject>(std::move(aObject)));
}

/**
 * @brief Adds a hidden object to the location.
 * 
 * @param aObject The object to add.
 */
void Location::addHiddenObject(GameObject *aObject)
{
    mHiddenObjects.push_back(Sean::Object<GameObject>(std::move(aObject)));
}

/**
 * @brief Adds an enemy to the location.
 * 
 * @param aEnemy The enemy to add.
 */
void Location::addEnemy(Enemy aEnemy)
{
    mEnemies.push_back(aEnemy);
}

/**
 * @brief Removes an enemy from the location by name.
 * 
 * @param aEnemyName The name of the enemy to remove.
 */
void Location::removeEnemy(const char *aEnemyName)
{
    for (auto iter = mEnemies.begin(); iter != mEnemies.end(); ++iter)
    {
        if (iter->getName() == aEnemyName)
        {
            mEnemies.erase(iter);
            return;
        }
    }
}

/**
 * @brief Sets an exit for the location.
 * 
 * @param aDirection The direction of the exit.
 * @param aLocation The location to set as the exit.
 */
void Location::setExit(Sean::Direction aDirection, Location *aLocation)
{
    if (aLocation == nullptr)
    {
        return;
    }
    switch (aDirection)
    {
    case Sean::Direction::North:
        mNorth = aLocation;
        break;
    case Sean::Direction::East:
        mEast = aLocation;
        break;
    case Sean::Direction::South:
        mSouth = aLocation;
        break;
    case Sean::Direction::West:
        mWest = aLocation;
        break;
    }
}

/**
 * @brief Gets the exit location in a given direction.
 * 
 * @param aDirection The direction of the exit.
 * @return The exit location.
 */
Location *Location::getExit(Sean::Direction aDirection) const
{
    switch (aDirection)
    {
    case Sean::Direction::North:
        return mNorth;
    case Sean::Direction::East:
        return mEast;
    case Sean::Direction::South:
        return mSouth;
    case Sean::Direction::West:
        return mWest;
    }
    return nullptr;
}

/**
 * @brief Gets the enemies in the location.
 * 
 * @return A reference to the vector of enemies.
 */
Sean::Vector<Enemy> &Location::getEnemies()
{
    return mEnemies;
}

/**
 * @brief Prints a short description of the location.
 */
void Location::printDescriptionShort() const
{
    std::cout << "Je staat in de locatie: " << mName << std::endl;
}

/**
 * @brief Prints a long description of the location.
 */
void Location::printDescriptionLong() const
{
    std::cout << "Je staat in de locatie: " << mName << std::endl;
    std::cout << mDescription << std::endl;
    std::cout << "Objecten:" << std::endl;
    if (mVisibleObjects.empty())
    {
        std::cout << "\tgeen" << std::endl;
    }
    else
    {
        for (const Sean::Object<GameObject> &obj : mVisibleObjects)
        {
            std::cout << "\t" << obj.get()->getName() << std::endl;
        }
    }
    std::cout << "Vijanden:" << std::endl;
    if (mEnemies.empty())
    {
        std::cout << "\tgeen" << std::endl;
    }
    else
    {
        for (const auto &enemy : mEnemies)
        {
            std::cout << "\t" << enemy.getName() << std::endl;
        }
    }
}

/**
 * @brief Prints the exits of the location.
 */
void Location::printExits() const
{
    std::cout << "Uitgangen: ";
    if (mNorth != nullptr)
    {
        std::cout << "noord ";
    }
    if (mEast != nullptr)
    {
        std::cout << "oost ";
    }
    if (mSouth != nullptr)
    {
        std::cout << "zuid ";
    }
    if (mWest != nullptr)
    {
        std::cout << "west ";
    }
    std::cout << std::endl;
}

/**
 * @brief Moves hidden objects to visible objects.
 */
void Location::moveHiddenObjects()
{
    for (Sean::Object<GameObject> &obj : mHiddenObjects)
    {
        mVisibleObjects.push_back(std::move(obj));
    }
    mHiddenObjects.clear();
}

/**
 * @brief Picks up an object from the location by name.
 * 
 * @param aObjectName The name of the object to pick up.
 * @return The picked up object.
 */
GameObject *Location::pickUpObject(const char *aObjectName)
{
    for (auto iter = mVisibleObjects.begin(); iter != mVisibleObjects.end(); ++iter)
    {
        if (iter->get()->getName() == aObjectName)
        {
            Sean::Object<GameObject> obj = std::move(*iter);
            mVisibleObjects.erase(iter);
            return obj.release();
        }
    }
    return nullptr;
}

/**
 * @brief Prints the details of an object or enemy by name.
 * 
 * @param aObjectName The name of the object or enemy to print.
 * @return True if the object or enemy was found and printed, false otherwise.
 */
bool Location::printObject(const char *aObjectName)
{
    for (const Sean::Object<GameObject> &obj : mVisibleObjects)
    {
        if (obj->getName() == aObjectName)
        {
            obj->printName();
            obj->printDescription();
            return true;
        }
    }

    for (Enemy &obj : mEnemies)
    {
        if (obj.getName() == aObjectName)
        {
            if (obj.isDead())
            {
                obj.printName();
                obj.printDescription();
                for (auto &hiddenObj : obj.getHiddenObjects())
                {
                    mVisibleObjects.push_back(Sean::Object(hiddenObj.release()));
                }
                obj.getHiddenObjects().clear();
                
                return true;
            }
            else
            {
                obj.printName();
                obj.printDescription();
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Gets the visible objects in the location.
 * 
 * @return A reference to the vector of visible objects.
 */
const Sean::Vector<Sean::Object<GameObject>> &Location::getVisibleObjects() const
{
    return mVisibleObjects;
}

/**
 * @brief Gets the hidden objects in the location.
 * 
 * @return A reference to the vector of hidden objects.
 */
const Sean::Vector<Sean::Object<GameObject>> &Location::getHiddenObjects() const
{
    return mHiddenObjects;
}

/**
 * @brief Gets the enemies in the location.
 * 
 * @return A reference to the vector of enemies.
 */
const Sean::Vector<Enemy> &Location::getEnemies() const
{
    return mEnemies;
}