#ifndef SEAN_H
#define SEAN_H

#include "Vector.h"
#include "String.h"
#include "SeanObject.h"
#include "Logger.h"

namespace Sean
{
    /**
     * @brief Enum class representing the type of an object.
     */
    enum class ObjectType
    {
        Gold,       ///< Represents gold.
        Weapon,     ///< Represents a weapon.
        Armor,      ///< Represents armor.
        Consumable  ///< Represents a consumable item.
    };

    /**
     * @brief Enum class representing the direction.
     */
    enum class Direction
    {
        North,      ///< Represents the north direction.
        East,       ///< Represents the east direction.
        South,      ///< Represents the south direction.
        West,       ///< Represents the west direction.
        Invalid     ///< Represents an invalid direction.
    };

    /**
     * @brief Struct representing direction information.
     */
    struct DirectionInfo
    {
        Direction mDirection; ///< The direction.
        int mID;              ///< The ID associated with the direction.
    };

    /**
     * @brief Struct representing parsed location information.
     */
    struct ParsedLocations
    {
        int mId;                           ///< The ID of the location.
        DirectionInfo mDirections[4];      ///< The directions associated with the location.
        Vector<String> mEnemies;           ///< The enemies in the location.
        Vector<String> mHiddenObjects;     ///< The hidden objects in the location.
        Vector<String> mVisibleObjects;    ///< The visible objects in the location.
        String mName;                      ///< The name of the location.
        String mDescription;               ///< The description of the location.

        /**
         * @brief Default constructor for ParsedLocations.
         */
        ParsedLocations() : mId(0), mDirections{{Direction::North, 0}, {Direction::East, 0}, {Direction::South, 0}, {Direction::West, 0}}, mEnemies(), mHiddenObjects(), mVisibleObjects(), mName(), mDescription() {}
    };

} // namespace Sean

#endif // SEAN_H