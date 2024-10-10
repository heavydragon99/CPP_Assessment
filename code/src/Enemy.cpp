#include "Enemy.h"

#include "GameObjectFactory.h"
#include "SqlReader.h"

Enemy::Enemy(Sean::String aName, Sean::String aDescription, int aHealth, int aAttackPercent, int aMinimumDamage, int aMaximumDamage, int aID)
    : mName(aName), mDescription(aDescription), mHealth(aHealth), mAttackPercent(aAttackPercent), mMinimumDamage(aMinimumDamage), mMaximumDamage(aMaximumDamage), mID(aID)
{
    // Get the amount of objects that the enemy has
    int minAmount;
    int maxAmount;
    SQLReader::getInstance().getObjectAmount(mName, minAmount, maxAmount);

    if(maxAmount <= 0)
    {
        return;
    }

    //TODO make different random
    int amount = rand() % (maxAmount - minAmount + 1) + minAmount;

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
                mHiddenObjects.push_back(*object.get());
            }
        }
    }
}

Sean::String Enemy::getName() const
{
    return mName + (std::to_string(mID).c_str());;
}