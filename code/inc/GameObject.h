#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Sean.h"
#include "IGameObject.h"

enum class ObjectType
{
    Gold,
    Weapon,
    Armor,
    Consumable_Health,
    Consumable_Experience,
    Consumable_Teleport
};

class GameObject : public IGameObject
{
public:
    GameObject() = default;
    GameObject(const Sean::String &aName, const Sean::String &aDescription, ObjectType aType, int aID);
    virtual ~GameObject() = default;

    virtual IGameObject* clone() const ;

    Sean::String getName() const override;
    void printName() const override;
    virtual void printDescription() const override;

    bool isWeapon() const override;
    bool isArmor() const override;
    bool isConsumable() const override;
    bool isMoney() const override;

    virtual int getValue() const override;

    ObjectType getType() const;

protected:
    Sean::String mName;        // Name of the object
    int mID;                   // ID of the object
    Sean::String mDescription; // Description of the object
    ObjectType mType;          // Type of the object
};

#endif // GAMEOBJECT_H