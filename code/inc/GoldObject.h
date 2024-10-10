#ifndef GOLD_OBJECT_H
#define GOLD_OBJECT_H

#include "GameObject.h"

class GoldObject : public GameObject
{
public:
    GoldObject(const Sean::String aName, const Sean::String aDescription, int aValue, ObjectType aType, int aID);
    virtual ~GoldObject() = default;

    int getValue() const;

private:
    int mAmount;
};

#endif // GOLD_OBJECT_H