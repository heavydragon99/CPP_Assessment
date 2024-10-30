#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Sean.h"

/**
 * @brief Represents an enemy in the game.
 * 
 * The Enemy class encapsulates the properties and behaviors of an enemy character,
 * including its name, description, health, attack capabilities, and hidden objects.
 */
class Enemy
{
public:
    // Constructors
    Enemy() = default;
    Enemy(Sean::String aName, Sean::String aDescription, int aHealth, int aAttackPercent, int aMinimumDamage, int aMaximumDamage, int aID);

    // Destructor
    ~Enemy() = default;

    // Assignment Operators
    Enemy(const Enemy &) = default;
    Enemy &operator=(const Enemy &) = default;
    Enemy(Enemy &&) noexcept = default;
    Enemy &operator=(Enemy &&) noexcept = default;

    // Methods
    Sean::String getName() const;
    void printName() const;
    void printDescription() const;
    bool isDead() const;
    Sean::Vector<Sean::Object<GameObject>> &getHiddenObjects();
    void takeDamage(int aDamage);
    int getAttack() const;

private:
    // Private Methods
    void initializeHiddenObjects();

private:
    // Members
    Sean::String mName;                                    ///< Name of the enemy
    int mID;                                               ///< ID of the enemy
    Sean::String mDescription;                             ///< Description of the enemy
    Sean::Vector<Sean::Object<GameObject>> mHiddenObjects; ///< Objects that are hidden in the enemy
    int mHealth;                                           ///< Health of the enemy
    int mAttackPercent;                                    ///< Attack percentage of the enemy
    int mMinimumDamage;                                    ///< Minimum damage the enemy can deal
    int mMaximumDamage;                                    ///< Maximum damage the enemy can deal
};

#endif // ENEMY_H