#include "ConsumableObject.h"

#include "RandomGenerator.h"

ConsumableObject::ConsumableObject(const Sean::String aName, const Sean::String aDescription, int aMinimum, int aMaximum, ObjectType aType, int aID)
    : GameObject(aName, aDescription, aType, aID), mMinimum(aMinimum), mMaximum(aMaximum)
{
}

// Copy Constructor
ConsumableObject::ConsumableObject(const ConsumableObject &other)
    : GameObject(other), mMinimum(other.mMinimum), mMaximum(other.mMaximum)
{
}

// Copy Assignment Operator
ConsumableObject &ConsumableObject::operator=(const ConsumableObject &other)
{
    if (this != &other)
    {
        GameObject::operator=(other);
        mMinimum = other.mMinimum;
        mMaximum = other.mMaximum;
    }
    return *this;
}

// Move Constructor
ConsumableObject::ConsumableObject(ConsumableObject &&other) noexcept
    : GameObject(std::move(other)), mMinimum(other.mMinimum), mMaximum(other.mMaximum)
{
    other.mMinimum = 0;
    other.mMaximum = 0;
}

// Move Assignment Operator
ConsumableObject &ConsumableObject::operator=(ConsumableObject &&other) noexcept
{
    if (this != &other)
    {
        GameObject::operator=(std::move(other));
        mMinimum = other.mMinimum;
        mMaximum = other.mMaximum;

        other.mMinimum = 0;
        other.mMaximum = 0;
    }
    return *this;
}

IGameObject *ConsumableObject::clone() const
{
    return new ConsumableObject(*this);
}

void ConsumableObject::printDescription() const
{
    std::cout << mDescription << std::endl;
    std::cout << "Sterkte tussen: " << mMinimum << " - " << mMaximum << std::endl;
}

int ConsumableObject::getValue() const
{
    RandomGenerator randomEngine;
    return randomEngine.getRandomValue(mMinimum, mMaximum);
}

int ConsumableObject::getMin() const
{
    return mMinimum;
}

int ConsumableObject::getMax() const
{
    return mMaximum;
}
