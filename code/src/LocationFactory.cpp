#include "LocationFactory.h"
#include "SqlReader.h"
#include <iostream>

int LocationFactory::mCounter = 0;

/**
 * @brief Creates a Location object with the specified name and description.
 *
 * @param aLocation The name of the location.
 * @param aDescription The description of the location.
 * @return Location* Pointer to the created Location object.
 */
Location *LocationFactory::createLocation(const Sean::String &aLocation, const Sean::String &aDescription)
{
    incrementCounter();
    return new Location(aLocation, aDescription, mCounter);
}

/**
 * @brief Creates a Location object with the specified name, description, and ID.
 *
 * @param aLocation The name of the location.
 * @param aDescription The description of the location.
 * @param aId The ID of the location.
 * @return Location* Pointer to the created Location object.
 */
Location *LocationFactory::createLocation(const Sean::String &aLocation, const Sean::String &aDescription, int aId)
{
    return new Location(aLocation, aDescription, aId);
}

/**
 * @brief Creates a random Location object.
 *
 * @return Location* Pointer to the created Location object.
 */
Location *LocationFactory::createLocation()
{
    Sean::String name;
    Sean::String description;
    try
    {
        if (SQLReader::getInstance().getRandomLocation(name, description))
        {
            incrementCounter();
            return new Location(name, description, mCounter);
        }
    }
    catch (std::exception &e)
    {
        throw std::runtime_error(e.what());
    }

    std::cerr << "Location not found in database" << std::endl;
    return nullptr;
}

/**
 * @brief Resets the internal counter for location IDs.
 */
void LocationFactory::resetCounter()
{
    mCounter = 0;
}

/**
 * @brief Increments the internal counter for location IDs.
 */
void LocationFactory::incrementCounter()
{
    ++mCounter;
}