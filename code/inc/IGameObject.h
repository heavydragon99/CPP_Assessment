#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include "Sean.h"

/**
 * @brief interface for game objects
 */
class IGameObject
{
public:
    // Constructors
    IGameObject() = default;

    // Destructor
    virtual ~IGameObject() = default;

    // Assignment Operators
    IGameObject(const IGameObject &) = default;
    IGameObject &operator=(const IGameObject &) = default;
    IGameObject(IGameObject &&) noexcept = default;
    IGameObject &operator=(IGameObject &&) noexcept = default;

    // Methods
    virtual IGameObject *clone() const = 0;
    virtual Sean::String getName() const = 0;
    virtual void printName() const = 0;
    virtual void printDescription() const = 0;
    virtual bool isWeapon() const = 0;
    virtual bool isArmor() const = 0;
    virtual bool isConsumableHealth() const = 0;
    virtual bool isConsumableExperience() const = 0;
    virtual bool isConsumableTeleport() const = 0;
    virtual bool isMoney() const = 0;
    virtual int getValue() const = 0;
    virtual int getMin() const = 0;
    virtual int getMax() const = 0;
};

#endif // IGAMEOBJECT_H