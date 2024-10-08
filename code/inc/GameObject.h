#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "CharArray.h"

enum class ObjectType
{
    Gold,
    Weapon,
    Armor,
    Consumable
};

class GameObject
{
public:

Sean::CharArray getName() const { return mName; }
Sean::CharArray getDescription() const { return mDescription; }

private:
Sean::CharArray mName; // Name of the object
Sean::CharArray mDescription; // Description of the object
ObjectType mType; // Type of the object
};

#endif // GAMEOBJECT_H