#include "ArmorObject.h"

ArmorObject::ArmorObject(const Sean::String aName, const Sean::String aDescription, int aArmor, ObjectType aType, int aID)
    : GameObject(aName, aDescription, aType, aID), mArmor(aArmor)
{
}

// Copy Constructor
ArmorObject::ArmorObject(const ArmorObject &other)
    : GameObject(other), mArmor(other.mArmor)
{
}

// Copy Assignment Operator
ArmorObject &ArmorObject::operator=(const ArmorObject &other)
{
    if (this != &other)
    {
        GameObject::operator=(other);
        mArmor = other.mArmor;
    }
    return *this;
}

// Move Constructor
ArmorObject::ArmorObject(ArmorObject &&other) noexcept
    : GameObject(std::move(other)), mArmor(other.mArmor)
{
    other.mArmor = 0;
}

// Move Assignment Operator
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

IGameObject *ArmorObject::clone() const
{
    return new ArmorObject(*this);
}

void ArmorObject::printDescription() const
{
    std::cout << mDescription << std::endl;
    std::cout << "Armor: " << mArmor << std::endl;
}

int ArmorObject::getArmor() const
{
    return mArmor;
}

int ArmorObject::getValue() const
{
    return getArmor();
}

int ArmorObject::getMin() const
{
    return getArmor();
}

int ArmorObject::getMax() const
{
    return getArmor();
}