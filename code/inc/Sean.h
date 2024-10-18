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
        West,
        Invalid
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

        ParsedLocations() : mId(0), mDirections{{Direction::North, 0}, {Direction::East, 0}, {Direction::South, 0}, {Direction::West, 0}}, mEnemies(), mHiddenObjects(), mVisibleObjects(), mName(), mDescription() {}
    };

} // namespace Sean

#endif // SEAN_H