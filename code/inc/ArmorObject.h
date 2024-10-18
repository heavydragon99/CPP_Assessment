#ifndef ARMOROBJECT_H
#define ARMOROBJECT_H

#include "GameObject.h"

class ArmorObject : public GameObject
{
public:
    ArmorObject(const Sean::String aName, const Sean::String aDescription, int aArmor, ObjectType aType, int aID);
    virtual ~ArmorObject() = default;

    int getArmor() const;
    int getValue() const override;

private:
    int mArmor;
};

#endif // ARMOROBJECT_H