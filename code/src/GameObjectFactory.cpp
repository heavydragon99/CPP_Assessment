#include "GameObjectFactory.h"

#include "GoldObject.h"
#include "WeaponObject.h"
#include "ArmorObject.h"
#include "ConsumableObject.h"
#include "SqlReader.h"
#include <iostream>


int GameObjectFactory::mCounter = 0;

/**
 * @brief Creates a GameObject with the specified name.
 * 
 * @param aObjectName The name of the object to create.
 * @return GameObject* The created object, or nullptr if the object was not found.
 */
GameObject *GameObjectFactory::createGameObject(const Sean::String &aObjectName)
{
    Sean::String name = aObjectName;
    Sean::String description;
    Sean::String type;
    int minValue;
    int maxValue;
    int protection;

    if (SQLReader::getInstance().getObjectInfo(name, description, type, minValue, maxValue, protection))
    {
        incrementCounter();
        if (type == "goudstukken")
        {
            return new GoldObject(name, description, minValue, maxValue, ObjectType::Gold, mCounter);
        }
        else if (type == "wapen")
        {
            return new WeaponObject(name, description, minValue, maxValue, ObjectType::Weapon, mCounter);
        }
        else if (type == "wapenrusting")
        {
            return new ArmorObject(name, description, protection, ObjectType::Armor, mCounter);
        }
        else if (type == "levenselixer" || type == "ervaringsdrank" || type == "teleportatiedrank")
        {
            ObjectType consumableType;
            if (type == "levenselixer")
                consumableType = ObjectType::Consumable_Health;
            else if (type == "ervaringsdrankje")
                consumableType = ObjectType::Consumable_Experience;
            else
                consumableType = ObjectType::Consumable_Teleport;

            return new ConsumableObject(name, description, minValue, maxValue, consumableType, mCounter);
        }
    }

    std::cerr << "Object not found: " << aObjectName << std::endl;
    return nullptr;
}

/**
 * @brief Creates a random GameObject.
 * 
 * @return GameObject* The created object, or nullptr if the object was not found.
 */
GameObject *GameObjectFactory::createGameObject()
{
    SQLReader &sqlReader = SQLReader::getInstance();
    Sean::String name;
    Sean::String description;
    Sean::String type;
    int minValue;
    int maxValue;
    int protection;

    if (sqlReader.getRandomObject(name, description, type, minValue, maxValue, protection))
    {
        incrementCounter();
        name.append(std::to_string(mCounter).c_str());
        if (type == "goudstukken")
        {
            return new GoldObject(name, description, minValue, maxValue, ObjectType::Gold, mCounter);
        }
        else if (type == "wapen")
        {
            return new WeaponObject(name, description, minValue, maxValue, ObjectType::Weapon, mCounter);
        }
        else if (type == "wapenrusting")
        {
            return new ArmorObject(name, description, protection, ObjectType::Armor, mCounter);
        }
        else if (type == "levenselixer" || type == "ervaringsdrank" || type == "teleportatiedrank")
        {
            ObjectType consumableType;
            if (type == "levenselixer")
                consumableType = ObjectType::Consumable_Health;
            else if (type == "ervaringsdrankje")
                consumableType = ObjectType::Consumable_Experience;
            else
                consumableType = ObjectType::Consumable_Teleport;

            return new ConsumableObject(name, description, minValue, maxValue, consumableType, mCounter);
        }
    }

    std::cerr << "Object not found in database" << std::endl;
    return nullptr;
}


/**
 * @brief Resets the counter for assigning unique IDs to game objects.
 */
void GameObjectFactory::resetCounter()
{
    mCounter = 0;
}

/**
 * @brief Increments the counter for assigning unique IDs to game objects.
 */
void GameObjectFactory::incrementCounter()
{
    ++mCounter;
}