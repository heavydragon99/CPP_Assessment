#include "XmlReader.h"
#include "tinyxml2.h"

#include <iostream>
#include <stdexcept>
#include <sstream>

/**
 * @brief Constructs an XmlReader object and parses the XML file.
 * @param aPath The path to the XML file to be read.
 * @throws std::runtime_error if the file cannot be loaded or the root element is not found.
 */
XmlReader::XmlReader(const char *aPath)
{
    tinyxml2::XMLDocument doc;

    // Load the file
    if (doc.LoadFile(aPath) != tinyxml2::XML_SUCCESS)
    {
        throw std::runtime_error(std::string("Failed to load file: ") + aPath);
    }

    // Get root element
    tinyxml2::XMLElement *root = doc.FirstChildElement("locaties");
    if (!root)
    {
        throw std::runtime_error("No 'locaties' element found in the file.");
    }

    // Iterate through each "locatie" element
    tinyxml2::XMLElement *loc = root->FirstChildElement("locatie");
    while (loc)
    {
        Sean::ParsedLocations location;
        loc->QueryIntAttribute("id", &location.mId);

        // Parse direction attributes
        const char *noord = loc->Attribute("noord");
        const char *oost = loc->Attribute("oost");
        const char *zuid = loc->Attribute("zuid");
        const char *west = loc->Attribute("west");

        int indexCounter = 0;

        if (noord != nullptr)
        {
            location.mDirections[indexCounter] = Sean::Direction::North;
            indexCounter++;
        }
        if (oost != nullptr)
        {
            location.mDirections[indexCounter] = Sean::Direction::East;
            indexCounter++;
        }
        if (zuid != nullptr)
        {
            location.mDirections[indexCounter] = Sean::Direction::South;
            indexCounter++;
        }
        if (west != nullptr)
        {
            location.mDirections[indexCounter] = Sean::Direction::West;
            indexCounter++;
        }

        // Parse enemies attribute
        const char *vijand = loc->Attribute("vijand");
        if (vijand)
        {
            std::string enemiesStr(vijand);
            std::istringstream enemiesStream(enemiesStr);
            std::string enemy;
            while (std::getline(enemiesStream, enemy, ';'))
            {
                location.mEnemies.push_back(enemy.c_str());
            }
        }

        // Parse hidden objects attribute
        const char *objectenverborgen = loc->Attribute("objectenverborgen");
        if (objectenverborgen)
        {
            std::string hiddenObjectsStr(objectenverborgen);
            std::istringstream hiddenObjectsStream(hiddenObjectsStr);
            std::string hiddenObject;
            while (std::getline(hiddenObjectsStream, hiddenObject, ';'))
            {
                location.mHiddenObjects.push_back(hiddenObject.c_str());
            }
        }

        // Parse visible objects attribute
        const char *objectenzichtbaar = loc->Attribute("objectenzichtbaar");
        if (objectenzichtbaar)
        {
            std::string visibleObjectsStr(objectenzichtbaar);
            std::istringstream visibleObjectsStream(visibleObjectsStr);
            std::string visibleObject;
            while (std::getline(visibleObjectsStream, visibleObject, ';'))
            {
                location.mVisibleObjects.push_back(visibleObject.c_str());
            }
        }

        // Parse name
        const char *name = loc->GetText();
        if (name)
        {
            location.mName = name;
        }

        // Parse description
        tinyxml2::XMLElement *descriptionElement = loc->FirstChildElement("beschrijving");
        if (descriptionElement)
        {
            const char *description = descriptionElement->GetText();
            if (description)
            {
                location.mDescription = description;
            }
        }

        // Add parsed location to the vector
        mParsedLocations.push_back(location);
        loc = loc->NextSiblingElement("locatie");
    }
}

/**
 * @brief Gets the parsed locations from the XML file.
 * @return A constant reference to a vector of parsed locations.
 */
const std::vector<Sean::ParsedLocations> &XmlReader::getLocations() const
{
    return mParsedLocations;
}