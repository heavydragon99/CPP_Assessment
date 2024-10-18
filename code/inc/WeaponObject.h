#ifndef WEAPONOBJECT_H
#define WEAPONOBJECT_H

#include "GameObject.h"

class WeaponObject : public GameObject
{
public:
    WeaponObject(const Sean::String aName, const Sean::String aDescription, int aMinDamage, int aMaxDamage, ObjectType aType, int aID);
    virtual ~WeaponObject() = default;

    WeaponObject(const WeaponObject &other);
    WeaponObject &operator=(const WeaponObject &other);
    WeaponObject(WeaponObject &&other) noexcept;
    WeaponObject &operator=(WeaponObject &&other) noexcept;

    IGameObject *clone() const override;

    void printDescription() const override;

    int getDamage() const;
    int getValue() const override;
    int getMin() const override;
    int getMax() const override;

private:
    int mMinDamage;
    int mMaxDamage;
};

#endif // WEAPONOBJECT_H