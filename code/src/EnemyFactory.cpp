#include "EnemyFactory.h"

#include "SqlReader.h"

int EnemyFactory::mCounter = 0;

Enemy *EnemyFactory::createEnemy(const Sean::String aEnemyName)
{

    Sean::String name = aEnemyName;
    Sean::String description;
    int health;
    int attackPercent;
    int minDamage;
    int maxDamage;

    if (SQLReader::getInstance().getEnemyInfo(name, description, health, attackPercent, minDamage, maxDamage))
    {
        return new Enemy(name, description, health, attackPercent, minDamage, maxDamage, mCounter++);
    }
    else
    {
        std::cerr << "Enemy not found: " << aEnemyName << std::endl;
        return nullptr;
    }
}

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
        return new Enemy(name, description, health, attackPercent, minDamage, maxDamage, mCounter++);
    }
    else
    {
        std::cerr << "Enemy not found in database" << std::endl;
        return nullptr;
    }
}