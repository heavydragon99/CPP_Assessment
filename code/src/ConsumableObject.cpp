#include "ConsumableObject.h"

ConsumableObject::ConsumableObject(const Sean::String aName, const Sean::String aDescription, int aMinimum, int aMaximum, ObjectType aType, int aID)
    : GameObject(aName, aDescription, aType, aID), mMinimum(aMinimum), mMaximum(aMaximum)
{}

int ConsumableObject::getValue() const
{
    throw std::runtime_error("getValue of ConsumableObject Not implemented");
}
