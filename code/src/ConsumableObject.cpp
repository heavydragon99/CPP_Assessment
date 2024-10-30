#include "ConsumableObject.h"
#include "RandomGenerator.h"
#include <iostream>
#include <utility>

// Constructors

/**
 * @brief Constructs a new ConsumableObject.
 * 
 * @param aName The name of the consumable object.
 * @param aDescription The description of the consumable object.
 * @param aMinimum The minimum value of the consumable object.
 * @param aMaximum The maximum value of the consumable object.
 * @param aType The type of the object.
 * @param aID The ID of the object.
 */
ConsumableObject::ConsumableObject(const Sean::String aName, const Sean::String aDescription, int aMinimum, int aMaximum, ObjectType aType, int aID)
    : GameObject(aName, aDescription, aType, aID), mMinimum(aMinimum), mMaximum(aMaximum)
{
}

/**
 * @brief Copy constructor.
 * 
 * @param other The other ConsumableObject to copy from.
 */
ConsumableObject::ConsumableObject(const ConsumableObject &other)
    : GameObject(other), mMinimum(other.mMinimum), mMaximum(other.mMaximum)
{
}

/**
 * @brief Move constructor.
 * 
 * @param other The other ConsumableObject to move from.
 */
ConsumableObject::ConsumableObject(ConsumableObject &&other) noexcept
    : GameObject(std::move(other)), mMinimum(other.mMinimum), mMaximum(other.mMaximum)
{
    other.mMinimum = 0;
    other.mMaximum = 0;
}

// Assignment Operators

/**
 * @brief Copy assignment operator.
 * 
 * @param other The other ConsumableObject to copy from.
 * @return ConsumableObject& A reference to this object.
 */
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

/**
 * @brief Move assignment operator.
 * 
 * @param other The other ConsumableObject to move from.
 * @return ConsumableObject& A reference to this object.
 */
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

// Methods

/**
 * @brief Clones the consumable object.
 * 
 * @return IGameObject* A pointer to the cloned object.
 */
IGameObject *ConsumableObject::clone() const
{
    return new ConsumableObject(*this);
}

/**
 * @brief Prints the description of the consumable object.
 */
void ConsumableObject::printDescription() const
{
    std::cout << mDescription << std::endl;
    std::cout << "Sterkte tussen: " << mMinimum << " - " << mMaximum << std::endl;
}

/**
 * @brief Gets a random value between the minimum and maximum values.
 * 
 * @return int The random value.
 */
int ConsumableObject::getValue() const
{
    RandomGenerator randomEngine;
    return randomEngine.getRandomValue(mMinimum, mMaximum);
}

/**
 * @brief Gets the minimum value of the consumable object.
 * 
 * @return int The minimum value.
 */
int ConsumableObject::getMin() const
{
    return mMinimum;
}

/**
 * @brief Gets the maximum value of the consumable object.
 * 
 * @return int The maximum value.
 */
int ConsumableObject::getMax() const
{
    return mMaximum;
}

// Private Methods

/**
 * @brief Swaps the contents of this object with another ConsumableObject.
 * 
 * @param other The other ConsumableObject to swap with.
 */
void ConsumableObject::swap(ConsumableObject &other) noexcept
{
    std::swap(mMinimum, other.mMinimum);
    std::swap(mMaximum, other.mMaximum);
}