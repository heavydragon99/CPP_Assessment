#include "LocationFactory.h"

#include "SqlReader.h"

Location *LocationFactory::createLocation(const char *aLocation, const char *aDescription)
{
    // SQLReader& sqlReader = SQLReader::getInstance();
    // Sean::CharArray name;
    // Sean::CharArray description;

    // if (sqlReader.getLocationInfo(aLocation, name, description))
    // {
    //     return new Location(name.get(), description.get());
    // }
    // else
    // {
    //     std::cerr << "Location not found in database: " << aLocation << std::endl;
    //     return nullptr;
    // }

    return new Location(aLocation, aDescription);
}

