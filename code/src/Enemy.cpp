#include "Enemy.h"

#include "GameObjectFactory.h"
#include "SqlReader.h"
#include "RandomGenerator.h"

Enemy::Enemy(Sean::String aName, Sean::String aDescription, int aHealth, int aAttackPercent, int aMinimumDamage, int aMaximumDamage, int aID)
    : mName(aName), mDescription(aDescription), mHealth(aHealth), mAttackPercent(aAttackPercent), mMinimumDamage(aMinimumDamage), mMaximumDamage(aMaximumDamage), mID(aID)
{
    // Get the amount of objects that the enemy has
    int minAmount;
    int maxAmount;
    SQLReader::getInstance().getObjectAmount(mName, minAmount, maxAmount);

    if (maxAmount <= 0)
    {
        return;
    }

    RandomGenerator randomEngine;
    int amount = randomEngine.getRandomValue(minAmount, maxAmount);

    // Get the objects that the enemy has
    for (int i = 0; i < amount; i++)
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

Sean::String Enemy::getName() const
{
    Sean::String tempName;
    if(isDead())
    {
        tempName = Sean::String("dode ") + mName + Sean::String(std::to_string(mID).c_str());
    }
    else
    {
        tempName = mName + Sean::String(std::to_string(mID).c_str());
    }
    return tempName;
}

void Enemy::printName() const
{
    std::cout << getName() << std::endl;
}

void Enemy::printDescription() const
{
    std::cout << mDescription << std::endl;
}

bool Enemy::isDead() const
{
    return mHealth <= 0;
}

Sean::Vector<Sean::Object<GameObject>> &Enemy::getHiddenObjects()
{
    return mHiddenObjects;
}

void Enemy::takeDamage(int aDamage)
{
    if(aDamage < 0)
    {
        return;
    }
    if(aDamage > mHealth)
    {
        mHealth = 0;
        return;
    }
    mHealth -= aDamage;
}

int Enemy::getAttack()
{
    RandomGenerator randomEngine;
    if (randomEngine.getChance(mAttackPercent))
    {
        return randomEngine.getRandomValue(mMinimumDamage, mMaximumDamage);
    }
    return 0;
}