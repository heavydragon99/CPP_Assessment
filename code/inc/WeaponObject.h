#ifndef WEAPONOBJECT_H
#define WEAPONOBJECT_H

#include "GameObject.h"

class WeaponObject : public GameObject
{
public:
    // Constructors
    WeaponObject(const Sean::String aName, const Sean::String aDescription, int aMinDamage, int aMaxDamage, ObjectType aType, int aID);
    WeaponObject(const WeaponObject &other);
    WeaponObject(WeaponObject &&other) noexcept;

    // Destructor
    virtual ~WeaponObject() = default;

    // Assignment Operators
    WeaponObject &operator=(const WeaponObject &other);
    WeaponObject &operator=(WeaponObject &&other) noexcept;

    // Methods
    IGameObject *clone() const override;
    void printDescription() const override;
    int getDamage() const;
    int getValue() const override;
    int getMin() const override;
    int getMax() const override;

private:
    // Private Methods
    void swap(WeaponObject &other) noexcept;

private:
    // Members
    int mMinDamage;
    int mMaxDamage;
};

#endif // WEAPONOBJECT_H