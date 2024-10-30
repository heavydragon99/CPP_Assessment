#include "RandomGenerator.h"

// Initialize the static member
std::default_random_engine RandomGenerator::mEngine{std::random_device{}()};

/**
 * @brief Gets a random value between aMin and aMax.
 * 
 * @param aMin The minimum value.
 * @param aMax The maximum value.
 * @return int The random value.
 */
int RandomGenerator::getRandomValue(int aMin, int aMax)
{
    std::uniform_int_distribution<int> distribution(aMin, aMax);
    return distribution(mEngine);
}

/**
 * @brief Gets a random chance based on a percentage.
 * 
 * @param aPercent The percentage chance.
 * @return bool True if the chance is successful, false otherwise.
 */
bool RandomGenerator::getChance(int aPercent)
{
    if (aPercent < 0 || aPercent > 100)
    {
        return false;
    }
    std::uniform_int_distribution<int> distribution(1, 100);
    return distribution(mEngine) <= aPercent;
}