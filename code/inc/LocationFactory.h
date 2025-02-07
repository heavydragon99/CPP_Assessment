#ifndef LOCATIONFACTORY_H
#define LOCATIONFACTORY_H

#include "Location.h"
#include "Sean.h"

/**
 * @brief factory class for creating locations
 */
class LocationFactory
{
public:
    // Constructors
    LocationFactory() = default;

    // Destructor
    virtual ~LocationFactory() = default;

    // Methods
    static Location *createLocation(const Sean::String &aLocation, const Sean::String &aDescription);
    static Location *createLocation(const Sean::String &aLocation, const Sean::String &aDescription,const int aId);
    static Location *createLocation();

    static void resetCounter();

private:
    // Private Methods
    static void incrementCounter();

private:
    // Members
    static int mCounter;
};

#endif // LOCATIONFACTORY_H