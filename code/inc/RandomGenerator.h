#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>

class RandomGenerator {
public:
    RandomGenerator() = default;

    int getRandomValue(int aMin, int aMax);
    bool getChance(int aPercent);

private:
    static std::default_random_engine mEngine;
};

#endif // RANDOMGENERATOR_H