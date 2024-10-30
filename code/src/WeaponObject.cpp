#include "WeaponObject.h"
#include "RandomGenerator.h"
#include <iostream>
#include <utility> // for std::swap

// Constructors

/**
 * @brief Constructs a WeaponObject with the specified attributes.
 * 
 * @param aName The name of the weapon object.
 * @param aDescription The description of the weapon object.
 * @param aMinDamage The minimum damage of the weapon object.
 * @param aMaxDamage The maximum damage of the weapon object.
 * @param aType The type of the weapon object.
 * @param aID The ID of the weapon object.
 */
WeaponObject::WeaponObject(const Sean::String aName, const Sean::String aDescription, int aMinDamage, int aMaxDamage, ObjectType aType, int aID)
    : GameObject(aName, aDescription, aType, aID), mMinDamage(aMinDamage), mMaxDamage(aMaxDamage)
{
}

/**
 * @brief Copy constructor for WeaponObject.
 * 
 * @param other The WeaponObject to copy.
 */
WeaponObject::WeaponObject(const WeaponObject &other)
    : GameObject(other), mMinDamage(other.mMinDamage), mMaxDamage(other.mMaxDamage)
{
}

/**
 * @brief Move constructor for WeaponObject.
 * 
 * @param other The WeaponObject to move.
 */
WeaponObject::WeaponObject(WeaponObject &&other) noexcept
    : GameObject(std::move(other)), mMinDamage(other.mMinDamage), mMaxDamage(other.mMaxDamage)
{
    other.mMinDamage = 0;
    other.mMaxDamage = 0;
}

// Assignment Operators

/**
 * @brief Copy assignment operator for WeaponObject.
 * 
 * @param other The WeaponObject to copy.
 * @return WeaponObject& Reference to the assigned WeaponObject.
 */
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

/**
 * @brief Move assignment operator for WeaponObject.
 * 
 * @param other The WeaponObject to move.
 * @return WeaponObject& Reference to the assigned WeaponObject.
 */
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

/**
 * @brief Clones the WeaponObject.
 * 
 * @return IGameObject* Pointer to the cloned WeaponObject.
 */
IGameObject *WeaponObject::clone() const
{
    return new WeaponObject(*this);
}

/**
 * @brief Prints the description of the WeaponObject.
 */
void WeaponObject::printDescription() const
{
    std::cout << mDescription << std::endl;
    std::cout << "Schade tussen: " << mMinDamage << " - " << mMaxDamage << std::endl;
}

/**
 * @brief Gets the damage of the WeaponObject.
 * 
 * @return int The damage of the WeaponObject.
 */
int WeaponObject::getDamage() const
{
    RandomGenerator randomEngine;
    return randomEngine.getRandomValue(mMinDamage, mMaxDamage);
}

/**
 * @brief Gets the value of the WeaponObject.
 * 
 * @return int The value of the WeaponObject.
 */
int WeaponObject::getValue() const
{
    return getDamage();
}

/**
 * @brief Gets the minimum damage of the WeaponObject.
 * 
 * @return int The minimum damage of the WeaponObject.
 */
int WeaponObject::getMin() const
{
    return mMinDamage;
}

/**
 * @brief Gets the maximum damage of the WeaponObject.
 * 
 * @return int The maximum damage of the WeaponObject.
 */
int WeaponObject::getMax() const
{
    return mMaxDamage;
}

// Private Methods

/**
 * @brief Swaps the contents of this WeaponObject with another.
 * 
 * @param other The WeaponObject to swap with.
 */
void WeaponObject::swap(WeaponObject &other) noexcept
{
    std::swap(mMinDamage, other.mMinDamage);
    std::swap(mMaxDamage, other.mMaxDamage);
}