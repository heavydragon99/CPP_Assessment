#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include "Enemy.h"
#include "Sean.h"

/**
 * @brief Factory class for creating Enemy objects.
 */
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

    static void resetCounter();

private:
    // Private Methods

    static void incrementCounter();

private:
    // Members
        /**
     * @brief Counter for assigning unique IDs to enemies.
     */
    static int mCounter;
};

#endif // ENEMY_FACTORY_H