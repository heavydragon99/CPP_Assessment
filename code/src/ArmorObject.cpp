#include "ArmorObject.h"

ArmorObject::ArmorObject(const Sean::String aName, const Sean::String aDescription, int aArmor, ObjectType aType, int aID)
    : GameObject(aName, aDescription, aType, aID), mArmor(aArmor)
{}

int ArmorObject::getArmor() const
{
    return mArmor;
}

int ArmorObject::getValue() const
{
    return getArmor();
}