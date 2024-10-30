#ifndef CONSUMABLEOBJECT_H
#define CONSUMABLEOBJECT_H

#include "GameObject.h"

/**
 * @class ConsumableObject
 * @brief A class representing a consumable object in the game.
 */
class ConsumableObject : public GameObject
{
public:
    // Constructors
    ConsumableObject(const Sean::String aName, const Sean::String aDescription, int aMinimum, int aMaximum, ObjectType aType, int aID);
    ConsumableObject(const ConsumableObject &other);
    ConsumableObject(ConsumableObject &&other) noexcept;

    // Destructor
    virtual ~ConsumableObject() = default;

    // Assignment Operators
    ConsumableObject &operator=(const ConsumableObject &other);
    ConsumableObject &operator=(ConsumableObject &&other) noexcept;

    // Methods
    IGameObject *clone() const override;
    void printDescription() const override;
    int getValue() const override;
    int getMin() const override;
    int getMax() const override;

private:
    // Private Methods
    void swap(ConsumableObject &other) noexcept;

private:
    /**
     * @brief The minimum value of the consumable object.
     */
    int mMinimum;

    /**
     * @brief The maximum value of the consumable object.
     */
    int mMaximum;
};

#endif // CONSUMABLEOBJECT_H