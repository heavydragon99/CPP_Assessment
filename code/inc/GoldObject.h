#ifndef GOLD_OBJECT_H
#define GOLD_OBJECT_H

#include "GameObject.h"

class GoldObject : public GameObject
{
public:
    // Constructors
    GoldObject(const Sean::String aName, const Sean::String aDescription, int aMinimumValue, int aMaximumValue, ObjectType aType, int aID);
    GoldObject(const GoldObject &other);
    GoldObject(GoldObject &&other) noexcept;

    // Destructor
    virtual ~GoldObject() = default;

    // Assignment Operators
    GoldObject &operator=(const GoldObject &other);
    GoldObject &operator=(GoldObject &&other) noexcept;

    // Methods
    IGameObject *clone() const override;
    void printDescription() const override;
    int getValue() const override;
    int getMin() const override;
    int getMax() const override;

private:
    // Private Methods

private:
    // Members
    int mMinimumValue;
    int mMaximumValue;
};

#endif // GOLD_OBJECT_H