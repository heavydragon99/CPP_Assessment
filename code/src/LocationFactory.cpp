#include "LocationFactory.h"
#include "SqlReader.h"
#include <iostream>

int LocationFactory::mCounter = 0;

Location *LocationFactory::createLocation(const Sean::String &aLocation, const Sean::String &aDescription)
{
    incrementCounter();
    return new Location(aLocation, aDescription, mCounter);
}

Location *LocationFactory::createLocation(const Sean::String &aLocation, const Sean::String &aDescription, int aId)
{
    return new Location(aLocation, aDescription, aId);
}

Location *LocationFactory::createLocation()
{
    SQLReader &sqlReader = SQLReader::getInstance();
    Sean::String name;
    Sean::String description;

    if (sqlReader.getRandomLocation(name, description))
    {
        incrementCounter();
        return new Location(name, description, mCounter);
    }
    else
    {
        std::cerr << "Location not found in database" << std::endl;
        return nullptr;
    }
}

// Private Methods
void LocationFactory::incrementCounter()
{
    ++mCounter;
}