#ifndef CONSUMABLEOBJECT_H
#define CONSUMABLEOBJECT_H

#include "GameObject.h"

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
    // Members
    int mMinimum;
    int mMaximum;
};

#endif // CONSUMABLEOBJECT_H