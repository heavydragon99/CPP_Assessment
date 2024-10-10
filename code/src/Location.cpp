#include "Location.h"
#include <iostream>

Location::Location(const Sean::String aName, const Sean::String aDescription, int aID)
    : mName(aName), mDescription(aDescription), mNorth(nullptr), mEast(nullptr), mSouth(nullptr), mWest(nullptr), mID(aID)
{}

Sean::String Location::getName() const {
    return mName + std::to_string(mID).c_str();
}

void Location::addVisibleObject(GameObject aObject) {
    mVisibleObjects.push_back(aObject);
}

void Location::addHiddenObject(GameObject aObject) {
    mHiddenObjects.push_back(aObject);
}

void Location::addEnemy(Enemy aEnemy) {
    mEnemies.push_back(aEnemy);
}

void Location::setExit(Sean::Direction aDirection, Location* aLocation) {
    if (aLocation == nullptr) {
        return;
    }
    switch (aDirection) {
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

void Location::printDescriptionShort() const {
    std::cout << "Name: " << mName << std::endl;
    for (const auto& enemy : mEnemies) {
        std::cout << "Enemies: " << enemy.getName() << std::endl;
    }
}

void Location::printDescriptionLong() const {
    std::cout << "Name: " << mName << std::endl;
    std::cout << "Description: " << mDescription << std::endl;
    for (const auto& obj : mVisibleObjects) {
        std::cout << "Visible Objects: " << obj.getName() << std::endl;
    }
    for (const auto& enemy : mEnemies) {
        std::cout << "Enemies: " << enemy.getName() << std::endl;
    }
}

void Location::update() {
    // Implementation for update
}