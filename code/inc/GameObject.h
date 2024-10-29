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
    // Constructors
    GameObject() = default;
    GameObject(const Sean::String &aName, const Sean::String &aDescription, ObjectType aType, int aID);
    GameObject(const GameObject &other);
    GameObject(GameObject &&other) noexcept;

    // Destructor
    virtual ~GameObject() = default;

    // Assignment Operators
    GameObject &operator=(const GameObject &other);
    GameObject &operator=(GameObject &&other) noexcept;

    // Methods
    virtual IGameObject *clone() const = 0;
    Sean::String getName() const override;
    void printName() const override;
    virtual void printDescription() const override = 0;
    bool isWeapon() const override;
    bool isArmor() const override;
    bool isConsumableHealth() const override;
    bool isConsumableExperience() const override;
    bool isConsumableTeleport() const override;
    bool isMoney() const override;
    virtual int getValue() const override = 0;
    virtual int getMin() const override = 0;
    virtual int getMax() const override = 0;
    ObjectType getType() const;

private:
    // Private Methods
    void swap(GameObject &other) noexcept;

protected:
    // Members
    Sean::String mName;        // Name of the object
    int mID;                   // ID of the object
    Sean::String mDescription; // Description of the object
    ObjectType mType;          // Type of the object
};

#endif // GAMEOBJECT_H