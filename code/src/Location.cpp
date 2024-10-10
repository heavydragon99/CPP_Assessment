#include "Location.h"
#include <iostream>

Location::Location(const char* aName, const char* aDescription)
    : mName(aName), mDescription(aDescription)
{}

Location::~Location() {
    // Destructor
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