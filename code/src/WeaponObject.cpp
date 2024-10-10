#include "WeaponObject.h"

#include <stdexcept>

WeaponObject::WeaponObject(const Sean::String aName, const Sean::String aDescription, int aMinDamage, int aMaxDamage, ObjectType aType, int aID)
    : GameObject(aName, aDescription, aType, aID), mMinDamage(aMinDamage), mMaxDamage(aMaxDamage)
{}

int WeaponObject::getDamage() const
{
    throw std::runtime_error("Function not implemented");
}