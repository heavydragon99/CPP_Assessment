#ifndef GOLD_OBJECT_H
#define GOLD_OBJECT_H

#include "GameObject.h"

class GoldObject : public GameObject
{
public:
    GoldObject(const Sean::String aName, const Sean::String aDescription, int aMinimumValue, int aMaximumValue, ObjectType aType, int aID);
    virtual ~GoldObject() = default;

    GoldObject(const GoldObject &other);
    GoldObject &operator=(const GoldObject &other);
    GoldObject(GoldObject &&other) noexcept;
    GoldObject &operator=(GoldObject &&other) noexcept;

    IGameObject* clone() const override;

    void printDescription() const override;

    int getValue() const override;
    int getMin() const override;
    int getMax() const override;

private:
    int mMinimumValue;
    int mMaximumValue;
};

#endif // GOLD_OBJECT_H