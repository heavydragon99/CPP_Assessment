#include "Location.h"

#include <iostream>

void Location::setName(const char* aName)
{
    mName = aName;
}

void Location::setDescription(const char* aDescription)
{
    mDescription = aDescription;
}

void Location::addVisibleObject(Sean::UniquePtr<GameObject> aObject)
{
    mVisibleObjects.push_back(aObject.move());
}

void Location::addHiddenObject(Sean::UniquePtr<GameObject> aObject)
{
    mHiddenObjects.push_back(aObject.move());
}

void Location::addEnemy(Sean::UniquePtr<Enemy> aEnemy)
{
    mEnemies.push_back(aEnemy.move());
}

void Location::printDescriptionShort()
{
    std::cout << "Name: " << mName << std::endl;
    for(int i = 0; i < mEnemies.size(); i++)
    {
        std::cout << "Enemies: " << mEnemies[i]->getName() << std::endl;
    }
}

void Location::printDescriptionLong()
{
    std::cout << "Name: " << mName << std::endl;
    std::cout << "Description: " << mDescription << std::endl;
    for(int i = 0; i < mVisibleObjects.size(); i++)
    {
        std::cout << "Visible Objects: " << mVisibleObjects[i]->getName() << std::endl;
    }
    for(int i = 0; i < mEnemies.size(); i++)
    {
        std::cout << "Enemies: " << mEnemies[i]->getName() << std::endl;
    }
}

void Location::update()
{}