#ifndef SEAN_H
#define SEAN_H

#include "Vector.h"
#include "String.h"
#include "SeanObject.h"

namespace Sean
{
    enum class ObjectType
    {
        Gold,
        Weapon,
        Armor,
        Consumable
    };

    enum class Direction
    {
        North,
        East,
        South,
        West
    };

    struct DirectionInfo
    {
        Direction mDirection;
        int mID;
    };

    struct ParsedLocations{
        int mId;
        DirectionInfo mDirections[4];
        Vector<String> mEnemies;
        Vector<String> mHiddenObjects;
        Vector<String> mVisibleObjects;
        String mName;
        String mDescription;
    };

} // namespace Sean

#endif // SEAN_H