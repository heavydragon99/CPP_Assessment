#include "GoldObject.h"
#include "RandomGenerator.h"
#include <iostream>

// Constructors
GoldObject::GoldObject(const Sean::String aName, const Sean::String aDescription, int aMinimumValue, int aMaximumValue, ObjectType aType, int aID)
    : GameObject(aName, aDescription, aType, aID), mMinimumValue(aMinimumValue), mMaximumValue(aMaximumValue)
{
}

// Copy Constructor
GoldObject::GoldObject(const GoldObject &other)
    : GameObject(other), mMinimumValue(other.mMinimumValue), mMaximumValue(other.mMaximumValue)
{
}

// Move Constructor
GoldObject::GoldObject(GoldObject &&other) noexcept
    : GameObject(std::move(other)), mMinimumValue(other.mMinimumValue), mMaximumValue(other.mMaximumValue)
{
    other.mMinimumValue = 0;
    other.mMaximumValue = 0;
}

// Assignment Operators
GoldObject &GoldObject::operator=(const GoldObject &other)
{
    if (this != &other)
    {
        GameObject::operator=(other);
        mMinimumValue = other.mMinimumValue;
        mMaximumValue = other.mMaximumValue;
    }
    return *this;
}

GoldObject &GoldObject::operator=(GoldObject &&other) noexcept
{
    if (this != &other)
    {
        GameObject::operator=(std::move(other));
        mMinimumValue = other.mMinimumValue;
        mMaximumValue = other.mMaximumValue;

        other.mMinimumValue = 0;
        other.mMaximumValue = 0;
    }
    return *this;
}

// Methods
IGameObject *GoldObject::clone() const
{
    return new GoldObject(*this);
}

void GoldObject::printDescription() const
{
    std::cout << mDescription << std::endl;
    std::cout << "Bevat tussen " << mMinimumValue << " - " << mMaximumValue << " goudstukken" << std::endl;
}

int GoldObject::getValue() const
{
    RandomGenerator randomEngine;
    return randomEngine.getRandomValue(mMinimumValue, mMaximumValue);
}

int GoldObject::getMin() const
{
    return mMinimumValue;
}

int GoldObject::getMax() const
{
    return mMaximumValue;
}