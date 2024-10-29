#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include "Enemy.h"
#include "Sean.h"

class EnemyFactory
{
public:
    // Constructors
    EnemyFactory() = default;

    // Destructor
    virtual ~EnemyFactory() = default;

    // Methods
    static Enemy *createEnemy(const Sean::String &aEnemyName);
    static Enemy *createEnemy();

private:
    // Private Methods
    static void incrementCounter();

private:
    // Members
    static int mCounter;
};

#endif // ENEMY_FACTORY_H