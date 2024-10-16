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

Location* Location::getExit(Sean::Direction aDirection) const {
    switch (aDirection) {
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

void Location::printDescriptionShort() const {
    std::cout << "Naam: " << mName << std::endl;
    for (const auto& enemy : mEnemies) {
        std::cout << "Vijanden: " << enemy.getName() << std::endl;
    }
}

void Location::printDescriptionLong() const {
    std::cout << "Naam: " << mName << std::endl;
    std::cout << "Omschrijving: " << mDescription << std::endl;
    for (const auto& obj : mVisibleObjects) {
        std::cout << "Objecten: " << obj.getName() << std::endl;
    }
    for (const auto& enemy : mEnemies) {
        std::cout << "Vijanden: " << enemy.getName() << std::endl;
    }
}

void Location::printExits() const {
    std::cout << "Uitgangen: ";
    if (mNorth != nullptr) {
        std::cout << "Noord ";
    }
    if (mEast != nullptr) {
        std::cout << "Oost ";
    }
    if (mSouth != nullptr) {
        std::cout << "Zuid ";
    }
    if (mWest != nullptr) {
        std::cout << "West ";
    }
    std::cout << std::endl;
}

void Location::update() {
    // Implementation for update
}