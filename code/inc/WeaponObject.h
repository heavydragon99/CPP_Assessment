#ifndef WEAPONOBJECT_H
#define WEAPONOBJECT_H

#include "GameObject.h"

/**
 * @brief The WeaponObject class represents a weapon in the game.
 */
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
    int mMinDamage; ///< The minimum damage of the weapon.
    int mMaxDamage; ///< The maximum damage of the weapon.
};

#endif // WEAPONOBJECT_H