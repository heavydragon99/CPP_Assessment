#ifndef LOCATIONFACTORY_H
#define LOCATIONFACTORY_H

#include "Location.h"

class LocationFactory
{
public:
    LocationFactory() = default;
    virtual ~LocationFactory() = default;

    static Location *createLocation(const Sean::String aLocation, const Sean::String aDescription);
    static Location *createLocation(const Sean::String aLocation, const Sean::String aDescription, int aId);
    static Location *createLocation();

    private:
    static int mCounter;
};

#endif // LOCATIONFACTORY_H