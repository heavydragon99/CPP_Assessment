#ifndef SEAN_H
#define SEAN_H

#include "Vector.h"
#include "UniquePtr.h"
#include "CharArray.h"

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
        Undefined,
        North,
        East,
        South,
        West
    };

    struct ParsedLocations{
        int mId;
        Direction mDirections[4];
        Vector<CharArray> mEnemies;
        Vector<CharArray> mHiddenObjects;
        Vector<CharArray> mVisibleObjects;
        CharArray mName;
        CharArray mDescription;
    };

} // namespace Sean

#endif // SEAN_H