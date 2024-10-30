#include "Enemy.h"
#include "GameObjectFactory.h"
#include "SqlReader.h"
#include "RandomGenerator.h"
#include <iostream>

// Constructors

/**
 * @brief Constructs an Enemy with the specified attributes.
 * 
 * @param aName The name of the enemy.
 * @param aDescription The description of the enemy.
 * @param aHealth The health of the enemy.
 * @param aAttackPercent The attack percentage of the enemy.
 * @param aMinimumDamage The minimum damage the enemy can deal.
 * @param aMaximumDamage The maximum damage the enemy can deal.
 * @param aID The ID of the enemy.
 */
Enemy::Enemy(Sean::String aName, Sean::String aDescription, int aHealth, int aAttackPercent, int aMinimumDamage, int aMaximumDamage, int aID)
    : mName(std::move(aName)), mDescription(std::move(aDescription)), mHealth(aHealth), mAttackPercent(aAttackPercent), mMinimumDamage(aMinimumDamage), mMaximumDamage(aMaximumDamage), mID(aID)
{
    initializeHiddenObjects();
}

// Methods

/**
 * @brief Gets the name of the enemy.
 * 
 * @return Sean::String The name of the enemy, with "dode " prefix if the enemy is dead.
 */
Sean::String Enemy::getName() const
{
    Sean::String tempName;
    if (isDead())
    {
        tempName = Sean::String("dode ") + mName + Sean::String(std::to_string(mID).c_str());
    }
    else
    {
        tempName = mName + Sean::String(std::to_string(mID).c_str());
    }
    return tempName;
}

/**
 * @brief Prints the name of the enemy to the standard output.
 */
void Enemy::printName() const
{
    std::cout << getName() << std::endl;
}

/**
 * @brief Prints the description of the enemy to the standard output.
 */
void Enemy::printDescription() const
{
    std::cout << mDescription << std::endl;
}

/**
 * @brief Checks if the enemy is dead.
 * 
 * @return bool True if the enemy's health is less than or equal to 0, false otherwise.
 */
bool Enemy::isDead() const
{
    return mHealth <= 0;
}

/**
 * @brief Gets the hidden objects of the enemy.
 * 
 * @return Sean::Vector<Sean::Object<GameObject>>& A reference to the vector of hidden objects.
 */
Sean::Vector<Sean::Object<GameObject>> &Enemy::getHiddenObjects()
{
    return mHiddenObjects;
}

/**
 * @brief Inflicts damage to the enemy.
 * 
 * @param aDamage The amount of damage to inflict. If the damage is greater than the enemy's health, the health is set to 0.
 */
void Enemy::takeDamage(int aDamage)
{
    if (aDamage < 0)
    {
        return;
    }
    if (aDamage > mHealth)
    {
        mHealth = 0;
        return;
    }
    mHealth -= aDamage;
}

/**
 * @brief Gets the attack value of the enemy.
 * 
 * @return int The attack value, which is a random value between the minimum and maximum damage if the attack is successful, otherwise 0.
 */
int Enemy::getAttack() const
{
    RandomGenerator randomEngine;
    if (randomEngine.getChance(mAttackPercent))
    {
        return randomEngine.getRandomValue(mMinimumDamage, mMaximumDamage);
    }
    return 0;
}

// Private Methods

/**
 * @brief Initializes the hidden objects of the enemy.
 * 
 * This method retrieves the amount of hidden objects from the database and creates them using the GameObjectFactory.
 */
void Enemy::initializeHiddenObjects()
{
    int minAmount;
    int maxAmount;
    if (!SQLReader::getInstance().getObjectAmount(mName, minAmount, maxAmount))
    {
        return;
    }

    if (maxAmount <= 0)
    {
        return;
    }

    RandomGenerator randomEngine;
    int amount = randomEngine.getRandomValue(minAmount, maxAmount);

    for (int i = 0; i < amount; ++i)
    {
        Sean::String name;
        Sean::String description;
        Sean::String type;
        int minValue;
        int maxValue;
        int protection;

        if (SQLReader::getInstance().getRandomObject(name, description, type, minValue, maxValue, protection))
        {
            Sean::Object<GameObject> object(GameObjectFactory::createGameObject(name));
            if (object.get() != nullptr)
            {
                mHiddenObjects.push_back(std::move(object));
            }
        }
    }
}