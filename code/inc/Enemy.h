#ifndef Enemy_H
#define Enemy_H

#include "GameObject.h"
#include "Sean.h"

class Enemy
{
public:
    Enemy() = default;
    Enemy(Sean::String aName, Sean::String aDescription, int aHealth, int aAttackPercent, int aMinimumDamage, int aMaximumDamage, int aID);

    Sean::String getName() const;

    void printName() const;
    void printDescription() const;
    bool isDead() const;
    Sean::Vector<Sean::Object<GameObject>>& getHiddenObjects();

    void takeDamage(int aDamage);
    int getAttack();

private:
    Sean::String mName;                      // Name of the enemy
    int mID;                                 // ID of the enemy
    Sean::String mDescription;               // Description of the enemy
    Sean::Vector<Sean::Object<GameObject>> mHiddenObjects; // Objects that are hidden in the enemy
    int mHealth;                             // Health of the enemy
    int mAttackPercent;                      // Attack percentage of the enemy
    int mMinimumDamage;                      // Minimum damage the enemy can deal
    int mMaximumDamage;                      // Maximum damage the enemy can deal
};

#endif // Enemy_H