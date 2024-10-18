#ifndef ARMOROBJECT_H
#define ARMOROBJECT_H

#include "GameObject.h"

class ArmorObject : public GameObject
{
public:
    ArmorObject(const Sean::String aName, const Sean::String aDescription, int aArmor, ObjectType aType, int aID);
    virtual ~ArmorObject() = default;

    ArmorObject(const ArmorObject &other);
    ArmorObject &operator=(const ArmorObject &other);
    ArmorObject(ArmorObject &&other) noexcept;
    ArmorObject &operator=(ArmorObject &&other) noexcept;

    IGameObject *clone() const override;

    void printDescription() const override;

    int getArmor() const;
    int getValue() const override;
    int getMin() const override;
    int getMax() const override;

private:
    int mArmor;
};

#endif // ARMOROBJECT_H