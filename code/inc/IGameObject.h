#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include "Sean.h"
#include <memory>

class IGameObject
{
public:
    IGameObject() = default;
    virtual ~IGameObject() = default;

    virtual IGameObject* clone() const = 0;

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

};

#endif // IGAMEOBJECT_H