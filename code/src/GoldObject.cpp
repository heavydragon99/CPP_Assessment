#include "GoldObject.h"
#include "RandomGenerator.h"
#include <iostream>

// Constructors

/**
 * @brief Constructs a GoldObject with the specified attributes.
 * 
 * @param aName The name of the gold object.
 * @param aDescription The description of the gold object.
 * @param aMinimumValue The minimum value of the gold object.
 * @param aMaximumValue The maximum value of the gold object.
 * @param aType The type of the gold object.
 * @param aID The ID of the gold object.
 */
GoldObject::GoldObject(const Sean::String aName, const Sean::String aDescription, int aMinimumValue, int aMaximumValue, ObjectType aType, int aID)
    : GameObject(aName, aDescription, aType, aID), mMinimumValue(aMinimumValue), mMaximumValue(aMaximumValue)
{
}

/**
 * @brief Copy constructor for GoldObject.
 * 
 * @param other The GoldObject to copy.
 */
GoldObject::GoldObject(const GoldObject &other)
    : GameObject(other), mMinimumValue(other.mMinimumValue), mMaximumValue(other.mMaximumValue)
{
}

/**
 * @brief Move constructor for GoldObject.
 * 
 * @param other The GoldObject to move.
 */
GoldObject::GoldObject(GoldObject &&other) noexcept
    : GameObject(std::move(other)), mMinimumValue(other.mMinimumValue), mMaximumValue(other.mMaximumValue)
{
    other.mMinimumValue = 0;
    other.mMaximumValue = 0;
}

// Assignment Operators

/**
 * @brief Copy assignment operator for GoldObject.
 * 
 * @param other The GoldObject to copy.
 * @return GoldObject& Reference to the assigned GoldObject.
 */
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

/**
 * @brief Move assignment operator for GoldObject.
 * 
 * @param other The GoldObject to move.
 * @return GoldObject& Reference to the assigned GoldObject.
 */
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

/**
 * @brief Clones the GoldObject.
 * 
 * @return IGameObject* Pointer to the cloned GoldObject.
 */
IGameObject *GoldObject::clone() const
{
    return new GoldObject(*this);
}

/**
 * @brief Prints the description of the GoldObject.
 */
void GoldObject::printDescription() const
{
    std::cout << mDescription << std::endl;
    std::cout << "Bevat tussen " << mMinimumValue << " - " << mMaximumValue << " goudstukken" << std::endl;
}

/**
 * @brief Gets the value of the GoldObject.
 * 
 * @return int The value of the GoldObject.
 */
int GoldObject::getValue() const
{
    RandomGenerator randomEngine;
    return randomEngine.getRandomValue(mMinimumValue, mMaximumValue);
}

/**
 * @brief Gets the minimum value of the GoldObject.
 * 
 * @return int The minimum value of the GoldObject.
 */
int GoldObject::getMin() const
{
    return mMinimumValue;
}

/**
 * @brief Gets the maximum value of the GoldObject.
 * 
 * @return int The maximum value of the GoldObject.
 */
int GoldObject::getMax() const
{
    return mMaximumValue;
}