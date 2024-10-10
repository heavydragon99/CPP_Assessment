#include "LocationFactory.h"

#include "SqlReader.h"

int LocationFactory::mCounter = 0;

Location *LocationFactory::createLocation(Sean::String aLocation, Sean::String aDescription)
{
    return new Location(aLocation, aDescription, mCounter++);
}

Location *LocationFactory::createLocation()
{
    SQLReader& sqlReader = SQLReader::getInstance();
    Sean::String name;
    Sean::String description;

    if (sqlReader.getRandomLocation(name, description))
    {
        return new Location(name.get(), description.get(), mCounter++);
    }
    else
    {
        std::cerr << "Location not found in database" << std::endl;
        return nullptr;
    }
}

