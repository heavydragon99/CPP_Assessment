#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Sean.h"

enum class ObjectType
{
    Gold,
    Weapon,
    Armor,
    Consumable_Health,
    Consumable_Experience,
    Consumable_Teleport
};

class GameObject
{
public:
    GameObject() = default;
    GameObject(const Sean::String &aName, const Sean::String &aDescription, ObjectType aType, int aID)
        : mName(aName), mDescription(aDescription), mType(aType), mID(aID)
    {}
    virtual ~GameObject() = default;

    Sean::String getName() const;
    void printName() const;;
    virtual void printDescription() const;
    ObjectType getType() const;

protected:
    Sean::String mName;        // Name of the object
    int mID;                   // ID of the object
    Sean::String mDescription; // Description of the object
    ObjectType mType;          // Type of the object
};

#endif // GAMEOBJECT_H