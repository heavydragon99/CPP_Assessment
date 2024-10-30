#include "Location.h"
#include <iostream>

// Constructors
Location::Location(const Sean::String aName, const Sean::String aDescription, int aID)
    : mName(aName), mDescription(aDescription), mNorth(nullptr), mEast(nullptr), mSouth(nullptr), mWest(nullptr), mID(aID)
{
}

// Methods
Sean::String Location::getName() const
{
    return mName + std::to_string(mID).c_str();
}

void Location::addVisibleObject(GameObject *aObject)
{
    mVisibleObjects.push_back(Sean::Object<GameObject>(std::move(aObject)));
}

void Location::addHiddenObject(GameObject *aObject)
{
    mHiddenObjects.push_back(Sean::Object<GameObject>(std::move(aObject)));
}

void Location::addEnemy(Enemy aEnemy)
{
    mEnemies.push_back(aEnemy);
}

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

Sean::Vector<Enemy> &Location::getEnemies()
{
    return mEnemies;
}

void Location::printDescriptionShort() const
{
    std::cout << "Je staat in de locatie: " << mName << std::endl;
}

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

void Location::printExits() const
{
    std::cout << "Uitgangen: ";
    if (mNorth != nullptr)
    {
        std::cout << "Noord ";
    }
    if (mEast != nullptr)
    {
        std::cout << "Oost ";
    }
    if (mSouth != nullptr)
    {
        std::cout << "Zuid ";
    }
    if (mWest != nullptr)
    {
        std::cout << "West ";
    }
    std::cout << std::endl;
}

void Location::moveHiddenObjects()
{
    for (Sean::Object<GameObject> &obj : mHiddenObjects)
    {
        mVisibleObjects.push_back(std::move(obj));
    }
    mHiddenObjects.clear();
}

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
                    mVisibleObjects.push_back(Sean::Object(std::move(hiddenObj.get())));
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

const Sean::Vector<Sean::Object<GameObject>> &Location::getVisibleObjects() const
{
    return mVisibleObjects;
}

const Sean::Vector<Sean::Object<GameObject>> &Location::getHiddenObjects() const
{
    return mHiddenObjects;
}