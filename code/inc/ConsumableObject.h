#ifndef CONSUMABLEOBJECT_H
#define CONSUMABLEOBJECT_H

#include "GameObject.h"

class ConsumableObject : public GameObject
{
public:
    ConsumableObject(const Sean::String aName, const Sean::String aDescription, int aMinimum, int aMaximum, ObjectType aType, int aID);
    virtual ~ConsumableObject() = default;

    ConsumableObject(const ConsumableObject &other);
    ConsumableObject &operator=(const ConsumableObject &other);
    ConsumableObject(ConsumableObject &&other) noexcept;
    ConsumableObject &operator=(ConsumableObject &&other) noexcept;

    IGameObject *clone() const override;

    void printDescription() const override;

    int getValue() const override;
    int getMin() const override;
    int getMax() const override;

private:
    int mMinimum;
    int mMaximum;
};

#endif // CONSUMABLEOBJECT_H