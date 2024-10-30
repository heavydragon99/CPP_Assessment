#include "GameObject.h"
#include <iostream>
#include <utility>

// Constructors

/**
 * @brief Constructs a GameObject with the specified attributes.
 * 
 * @param aName The name of the object.
 * @param aDescription The description of the object.
 * @param aType The type of the object.
 * @param aID The ID of the object.
 */
GameObject::GameObject(const Sean::String &aName, const Sean::String &aDescription, ObjectType aType, int aID)
    : mName(aName), mDescription(aDescription), mType(aType), mID(aID)
{
}

/**
 * @brief Copy constructor for GameObject.
 * 
 * @param other The GameObject to copy.
 */
GameObject::GameObject(const GameObject &other)
    : mName(other.mName), mID(other.mID), mDescription(other.mDescription), mType(other.mType)
{
}

/**
 * @brief Move constructor for GameObject.
 * 
 * @param other The GameObject to move.
 */
GameObject::GameObject(GameObject &&other) noexcept
    : mName(std::move(other.mName)), mID(other.mID), mDescription(std::move(other.mDescription)), mType(other.mType)
{
    other.mID = 0;
    other.mType = ObjectType::Gold; // Default type
}

// Assignment Operators

/**
 * @brief Copy assignment operator for GameObject.
 * 
 * @param other The GameObject to copy.
 * @return GameObject& Reference to the assigned GameObject.
 */
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

/**
 * @brief Move assignment operator for GameObject.
 * 
 * @param other The GameObject to move.
 * @return GameObject& Reference to the assigned GameObject.
 */
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

/**
 * @brief Gets the name of the object.
 * 
 * @return Sean::String The name of the object.
 */
Sean::String GameObject::getName() const
{
    return mName + (std::to_string(mID).c_str());
}

/**
 * @brief Prints the name of the object to the standard output.
 */
void GameObject::printName() const
{
    std::cout << getName() << std::endl;
}

/**
 * @brief Checks if the object is a weapon.
 * 
 * @return bool True if the object is a weapon, false otherwise.
 */
bool GameObject::isWeapon() const
{
    return mType == ObjectType::Weapon;
}

/**
 * @brief Checks if the object is armor.
 * 
 * @return bool True if the object is armor, false otherwise.
 */
bool GameObject::isArmor() const
{
    return mType == ObjectType::Armor;
}

/**
 * @brief Checks if the object is a health consumable.
 * 
 * @return bool True if the object is a health consumable, false otherwise.
 */
bool GameObject::isConsumableHealth() const
{
    return mType == ObjectType::Consumable_Health;
}

/**
 * @brief Checks if the object is an experience consumable.
 * 
 * @return bool True if the object is an experience consumable, false otherwise.
 */
bool GameObject::isConsumableExperience() const
{
    return mType == ObjectType::Consumable_Experience;
}

/**
 * @brief Checks if the object is a teleport consumable.
 * 
 * @return bool True if the object is a teleport consumable, false otherwise.
 */
bool GameObject::isConsumableTeleport() const
{
    return mType == ObjectType::Consumable_Teleport;
}

/**
 * @brief Checks if the object is money (gold).
 * 
 * @return bool True if the object is money, false otherwise.
 */
bool GameObject::isMoney() const
{
    return mType == ObjectType::Gold;
}

/**
 * @brief Gets the type of the object.
 * 
 * @return ObjectType The type of the object.
 */
ObjectType GameObject::getType() const
{
    return mType;
}

// Private Methods

/**
 * @brief Swaps the contents of this GameObject with another.
 * 
 * @param other The GameObject to swap with.
 */
void GameObject::swap(GameObject &other) noexcept
{
    std::swap(mName, other.mName);
    std::swap(mID, other.mID);
    std::swap(mDescription, other.mDescription);
    std::swap(mType, other.mType);
}