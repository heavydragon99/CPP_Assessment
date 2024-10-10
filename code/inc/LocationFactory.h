#ifndef LOCATIONFACTORY_H
#define LOCATIONFACTORY_H

#include "Location.h"

class LocationFactory
{
public:
    LocationFactory() = default;
    virtual ~LocationFactory() = default;

    static Location *createLocation(const char *aLocation, const char *aDescription);
};

#endif // LOCATIONFACTORY_H