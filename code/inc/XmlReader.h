#ifndef XMLREADER_H
#define XMLREADER_H

#include <string>
#include <vector>
#include "Sean.h"

/**
 * @class XmlReader
 * @brief A class to read and parse XML files.
 */
class XmlReader
{
public:
    XmlReader(const char *aPath);
    const std::vector<Sean::ParsedLocations> &getLocations() const;

private:
    std::vector<Sean::ParsedLocations> mParsedLocations; ///< Vector to store parsed locations.
};

#endif // XMLREADER_H