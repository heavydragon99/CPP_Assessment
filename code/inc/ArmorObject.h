#ifndef ARMOROBJECT_H
#define ARMOROBJECT_H

#include "GameObject.h"
#include <utility> // for std::move

class ArmorObject : public GameObject
{
public:
    // Constructors
    ArmorObject(const Sean::String aName, const Sean::String aDescription, int aArmor, ObjectType aType, int aID);
    ArmorObject(const ArmorObject &other);
    ArmorObject(ArmorObject &&other) noexcept;

    // Destructor
    virtual ~ArmorObject() = default;

        // Assignment Operators
    ArmorObject &operator=(const ArmorObject &other);
    ArmorObject &operator=(ArmorObject &&other) noexcept;

    // Methods
    IGameObject *clone() const override;
    void printDescription() const override;
    int getArmor() const;
    int getValue() const override;
    int getMin() const override;
    int getMax() const override;



private:
    // Private Methods
    void swap(ArmorObject &other) noexcept;

    // Members
    int mArmor;
};

#endif // ARMOROBJECT_H