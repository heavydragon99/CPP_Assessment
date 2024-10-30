#include "ArmorObject.h"
#include <iostream>
#include <utility>

// Constructors

/**
 * @brief Constructs an ArmorObject with the given parameters.
 * @param aName The name of the armor object.
 * @param aDescription The description of the armor object.
 * @param aArmor The armor value.
 * @param aType The type of the object.
 * @param aID The ID of the object.
 */
ArmorObject::ArmorObject(const Sean::String aName, const Sean::String aDescription, int aArmor, ObjectType aType, int aID)
    : GameObject(aName, aDescription, aType, aID), mArmor(aArmor)
{
}

/**
 * @brief Copy constructor.
 * @param other The other ArmorObject to copy from.
 */
ArmorObject::ArmorObject(const ArmorObject &other)
    : GameObject(other), mArmor(other.mArmor)
{
}

/**
 * @brief Move constructor.
 * @param other The other ArmorObject to move from.
 */
ArmorObject::ArmorObject(ArmorObject &&other) noexcept
    : GameObject(std::move(other)), mArmor(other.mArmor)
{
    other.mArmor = 0;
}

// Assignment Operators

/**
 * @brief Copy assignment operator.
 * @param other The other ArmorObject to copy from.
 * @return Reference to this ArmorObject.
 */
ArmorObject &ArmorObject::operator=(const ArmorObject &other)
{
    if (this != &other)
    {
        GameObject::operator=(other);
        mArmor = other.mArmor;
    }
    return *this;
}

/**
 * @brief Move assignment operator.
 * @param other The other ArmorObject to move from.
 * @return Reference to this ArmorObject.
 */
ArmorObject &ArmorObject::operator=(ArmorObject &&other) noexcept
{
    if (this != &other)
    {
        GameObject::operator=(std::move(other));
        mArmor = other.mArmor;
        other.mArmor = 0;
    }
    return *this;
}

// Methods

/**
 * @brief Clones the ArmorObject.
 * @return A pointer to the cloned ArmorObject.
 */
IGameObject *ArmorObject::clone() const
{
    return new ArmorObject(*this);
}

/**
 * @brief Prints the description of the ArmorObject.
 */
void ArmorObject::printDescription() const
{
    std::cout << mDescription << std::endl;
    std::cout << "Armor: " << mArmor << std::endl;
}

/**
 * @brief Gets the armor value.
 * @return The armor value.
 */
int ArmorObject::getArmor() const
{
    return mArmor;
}

/**
 * @brief Gets the value of the ArmorObject.
 * @return The value of the ArmorObject.
 */
int ArmorObject::getValue() const
{
    return getArmor();
}

/**
 * @brief Gets the minimum value of the ArmorObject.
 * @return The minimum value of the ArmorObject.
 */
int ArmorObject::getMin() const
{
    return getArmor();
}

/**
 * @brief Gets the maximum value of the ArmorObject.
 * @return The maximum value of the ArmorObject.
 */
int ArmorObject::getMax() const
{
    return getArmor();
}

// Private Methods

/**
 * @brief Swaps the contents of this ArmorObject with another.
 * @param other The other ArmorObject to swap with.
 */
void ArmorObject::swap(ArmorObject &other) noexcept
{
    std::swap(mArmor, other.mArmor);
}