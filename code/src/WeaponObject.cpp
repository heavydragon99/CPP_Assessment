#include "WeaponObject.h"

#include "RandomGenerator.h"

#include <stdexcept>

WeaponObject::WeaponObject(const Sean::String aName, const Sean::String aDescription, int aMinDamage, int aMaxDamage, ObjectType aType, int aID)
    : GameObject(aName, aDescription, aType, aID), mMinDamage(aMinDamage), mMaxDamage(aMaxDamage)
{
}

// Copy Constructor
WeaponObject::WeaponObject(const WeaponObject &other)
    : GameObject(other), mMinDamage(other.mMinDamage), mMaxDamage(other.mMaxDamage)
{
}

// Copy Assignment Operator
WeaponObject &WeaponObject::operator=(const WeaponObject &other)
{
    if (this != &other)
    {
        GameObject::operator=(other);
        mMinDamage = other.mMinDamage;
        mMaxDamage = other.mMaxDamage;
    }
    return *this;
}

// Move Constructor
WeaponObject::WeaponObject(WeaponObject &&other) noexcept
    : GameObject(std::move(other)), mMinDamage(other.mMinDamage), mMaxDamage(other.mMaxDamage)
{
    other.mMinDamage = 0;
    other.mMaxDamage = 0;
}

// Move Assignment Operator
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
