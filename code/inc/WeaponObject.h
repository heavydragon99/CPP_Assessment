#ifndef WEAPONOBJECT_H
#define WEAPONOBJECT_H

#include "GameObject.h"

class WeaponObject : public GameObject
{
public:
    WeaponObject(const Sean::String aName, const Sean::String aDescription, int aMinDamage, int aMaxDamage, ObjectType aType, int aID);
    virtual ~WeaponObject() = default;

    int getDamage() const;

private:
    int mMinDamage;
    int mMaxDamage;
};

#endif // WEAPONOBJECT_H