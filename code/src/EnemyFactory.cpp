#include "EnemyFactory.h"
#include "SqlReader.h"
#include <iostream>

int EnemyFactory::mCounter = 0;

/**
 * @brief Creates an Enemy object with the specified name.
 * 
 * @param aEnemyName The name of the enemy to create.
 * @return Enemy* Pointer to the created Enemy object.
 */
Enemy *EnemyFactory::createEnemy(const Sean::String &aEnemyName)
{
    Sean::String name = aEnemyName;
    Sean::String description;
    int health;
    int attackPercent;
    int minDamage;
    int maxDamage;

    if (SQLReader::getInstance().getEnemyInfo(name, description, health, attackPercent, minDamage, maxDamage))
    {
        incrementCounter();
        return new Enemy(name, description, health, attackPercent, minDamage, maxDamage, mCounter);
    }
    else
    {
        std::cerr << "Enemy not found: " << aEnemyName << std::endl;
        return nullptr;
    }
}

/**
 * @brief Creates a random Enemy object.
 * 
 * @return Enemy* Pointer to the created Enemy object.
 */
Enemy *EnemyFactory::createEnemy()
{
    SQLReader &sqlReader = SQLReader::getInstance();
    Sean::String name;
    Sean::String description;
    int health;
    int attackPercent;
    int minDamage;
    int maxDamage;

    if (sqlReader.getRandomEnemy(name, description, health, attackPercent, minDamage, maxDamage))
    {
        incrementCounter();
        return new Enemy(name, description, health, attackPercent, minDamage, maxDamage, mCounter);
    }
    else
    {
        std::cerr << "Enemy not found in database" << std::endl;
        return nullptr;
    }
}

void EnemyFactory::resetCounter()
{
    mCounter = 0;
}

/**
 * @brief Increments the internal counter for enemy IDs.
 */
void EnemyFactory::incrementCounter()
{
    ++mCounter;
}