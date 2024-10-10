#include "GoldObject.h"

GoldObject::GoldObject(const Sean::String aName, const Sean::String aDescription, int aValue, ObjectType aType, int aID)
    : GameObject(aName, aDescription, aType, aID), mAmount(aValue)
{}

int GoldObject::getValue() const
{
    return mAmount;
}