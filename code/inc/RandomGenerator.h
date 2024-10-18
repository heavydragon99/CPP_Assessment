#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>

class RandomGenerator {
public:
    RandomGenerator() = default;

    int getRandomValue(int aMin, int aMax);
    bool shouldAttack(int aAttackPercent);

private:
    static std::default_random_engine mEngine;
};

#endif // RANDOMGENERATOR_H