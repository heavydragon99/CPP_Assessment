#ifndef Enemy_H
#define Enemy_H

#include "GameObject.h"
#include "Sean.h"

class Enemy
{
public:

    Sean::CharArray getName() const; 

private:
    Sean::CharArray mName; // Name of the enemy
    Sean::CharArray mDescription; // Description of the enemy
    int mHealth; // Health of the enemy
    int mAttackPercent; // Attack percentage of the enemy
    Sean::Vector<Sean::UniquePtr<GameObject>> mHiddenObjects; // Objects that are hidden in the enemy
    int mMinimumDamage; // Minimum damage the enemy can deal
    int mMaximumDamage; // Maximum damage the enemy can deal
};

#endif // Enemy_H