#include "GameObject.h"
#include <iostream>
#include <utility> // for std::swap

// Constructors
GameObject::GameObject(const Sean::String &aName, const Sean::String &aDescription, ObjectType aType, int aID)
    : mName(aName), mDescription(aDescription), mType(aType), mID(aID)
{
}

// Copy Constructor
GameObject::GameObject(const GameObject &other)
    : mName(other.mName), mID(other.mID), mDescription(other.mDescription), mType(other.mType)
{
}

// Move Constructor
GameObject::GameObject(GameObject &&other) noexcept
    : mName(std::move(other.mName)), mID(other.mID), mDescription(std::move(other.mDescription)), mType(other.mType)
{
    other.mID = 0;
    other.mType = ObjectType::Gold; // Default type
}

// Assignment Operators
GameObject &GameObject::operator=(const GameObject &other)
{
    if (this != &other)
    {
        mName = other.mName;
        mID = other.mID;
        mDescription = other.mDescription;
        mType = other.mType;
    }
    return *this;
}

GameObject &GameObject::operator=(GameObject &&other) noexcept
{
    if (this != &other)
    {
        mName = std::move(other.mName);
        mID = other.mID;
        mDescription = std::move(other.mDescription);
        mType = other.mType;

        other.mID = 0;
        other.mType = ObjectType::Gold; // Default type
    }
    return *this;
}

// Methods
Sean::String GameObject::getName() const
{
    return mName + (std::to_string(mID).c_str());
}

void GameObject::printName() const
{
    std::cout << getName() << std::endl;
}

bool GameObject::isWeapon() const
{
    return mType == ObjectType::Weapon;
}

bool GameObject::isArmor() const
{
    return mType == ObjectType::Armor;
}

bool GameObject::isConsumableHealth() const
{
    return mType == ObjectType::Consumable_Health;
}

bool GameObject::isConsumableExperience() const
{
    return mType == ObjectType::Consumable_Experience;
}

bool GameObject::isConsumableTeleport() const
{
    return mType == ObjectType::Consumable_Teleport;
}

bool GameObject::isMoney() const
{
    return mType == ObjectType::Gold;
}

ObjectType GameObject::getType() const
{
    return mType;
}

// Private Methods
void GameObject::swap(GameObject &other) noexcept
{
    std::swap(mName, other.mName);
    std::swap(mID, other.mID);
    std::swap(mDescription, other.mDescription);
    std::swap(mType, other.mType);
}