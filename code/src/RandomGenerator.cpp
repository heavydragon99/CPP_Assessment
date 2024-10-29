#include "RandomGenerator.h"

// Initialize the static member
std::default_random_engine RandomGenerator::mEngine{std::random_device{}()};

int RandomGenerator::getRandomValue(int aMin, int aMax)
{
    std::uniform_int_distribution<int> distribution(aMin, aMax);
    return distribution(mEngine);
}

bool RandomGenerator::getChance(int aPercent)
{
    if (aPercent < 0 || aPercent > 100)
    {
        return false;
    }
    std::uniform_int_distribution<int> distribution(1, 100);
    return distribution(mEngine) <= aPercent;
}