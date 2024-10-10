#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include "Enemy.h"

class EnemyFactory
{
public:
    EnemyFactory() = default;
    virtual ~EnemyFactory() = default;

    static Enemy *createEnemy(const Sean::String aEnemyName);
    static Enemy *createEnemy();

    private:
    static int mCounter;
};

#endif // ENEMY_FACTORY_H