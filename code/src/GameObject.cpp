#include "GameObject.h"

#include <iostream>

GameObject::GameObject(const Sean::String &aName, const Sean::String &aDescription, ObjectType aType, int aID)
        : mName(aName), mDescription(aDescription), mType(aType), mID(aID)
    {}

IGameObject* GameObject::clone() const
{
    return new GameObject(*this); // Copy constructor
}

Sean::String GameObject::getName() const
{
    return mName + (std::to_string(mID).c_str());
}

void GameObject::printName() const
{
    std::cout << getName() << std::endl;
}

void GameObject::printDescription() const
{
    std::cout << mDescription << std::endl;
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

int GameObject::getValue() const
{
    return 0;
}
