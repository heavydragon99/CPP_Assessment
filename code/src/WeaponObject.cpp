#include "WeaponObject.h"
#include "RandomGenerator.h"
#include <iostream>
#include <utility> // for std::swap

// Constructors
WeaponObject::WeaponObject(const Sean::String aName, const Sean::String aDescription, int aMinDamage, int aMaxDamage, ObjectType aType, int aID)
    : GameObject(aName, aDescription, aType, aID), mMinDamage(aMinDamage), mMaxDamage(aMaxDamage)
{
}

// Copy Constructor
WeaponObject::WeaponObject(const WeaponObject &other)
    : GameObject(other), mMinDamage(other.mMinDamage), mMaxDamage(other.mMaxDamage)
{
}

// Move Constructor
WeaponObject::WeaponObject(WeaponObject &&other) noexcept
    : GameObject(std::move(other)), mMinDamage(other.mMinDamage), mMaxDamage(other.mMaxDamage)
{
    other.mMinDamage = 0;
    other.mMaxDamage = 0;
}

// Assignment Operators
WeaponObject &WeaponObject::operator=(const WeaponObject &other)
{
    if (this != &other)
    {
        WeaponObject temp(other);
        swap(temp);
    }
    return *this;
}

WeaponObject &WeaponObject::operator=(WeaponObject &&other) noexcept
{
    if (this != &other)
    {
        GameObject::operator=(std::move(other));
        mMinDamage = other.mMinDamage;
        mMaxDamage = other.mMaxDamage;

        other.mMinDamage = 0;
        other.mMaxDamage = 0;
    }
    return *this;
}

// Methods
IGameObject *WeaponObject::clone() const
{
    return new WeaponObject(*this);
}

void WeaponObject::printDescription() const
{
    std::cout << mDescription << std::endl;
    std::cout << "Schade tussen: " << mMinDamage << " - " << mMaxDamage << std::endl;
}

int WeaponObject::getDamage() const
{
    RandomGenerator randomEngine;
    return randomEngine.getRandomValue(mMinDamage, mMaxDamage);
}

int WeaponObject::getValue() const
{
    return getDamage();
}

int WeaponObject::getMin() const
{
    return mMinDamage;
}

int WeaponObject::getMax() const
{
    return mMaxDamage;
}

// Private Methods
void WeaponObject::swap(WeaponObject &other) noexcept
{
    std::swap(mMinDamage, other.mMinDamage);
    std::swap(mMaxDamage, other.mMaxDamage);
}