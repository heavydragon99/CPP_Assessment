#ifndef CONSUMABLEOBJECT_H
#define CONSUMABLEOBJECT_H

#include "GameObject.h"

class ConsumableObject : public GameObject
{
public:
    ConsumableObject(const Sean::String aName, const Sean::String aDescription, int aMinimum, int aMaximum, ObjectType aType, int aID);
    virtual ~ConsumableObject() = default;

private:
    int mMinimum;
    int mMaximum;
};

#endif // CONSUMABLEOBJECT_H