#include "GameObjectFactory.h"

#include "GoldObject.h"
#include "WeaponObject.h"
#include "ArmorObject.h"
#include "ConsumableObject.h"
#include "SqlReader.h"

int GameObjectFactory::mCounter = 0;

GameObject *GameObjectFactory::createGameObject(const Sean::String aObjectName)
{
    Sean::String name = aObjectName;
    Sean::String description;
    Sean::String type;
    int minValue;
    int maxValue;
    int protection;

    if (SQLReader::getInstance().getObjectInfo(name, description, type, minValue, maxValue, protection))
    {
        if (type == "goudstukken")
        {
            return new GoldObject(name, description, minValue, ObjectType::Gold, mCounter++);
        }
        else if (type == "wapen")
        {
            return new WeaponObject(name, description, minValue, maxValue, ObjectType::Weapon, mCounter++);
        }
        else if (type == "wapenrusting")
        {
            return new ArmorObject(name, description, protection, ObjectType::Armor, mCounter++);
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

            return new ConsumableObject(name, description, minValue, maxValue, consumableType, mCounter++);
        }
    }

    std::cerr << "Object not found: " << aObjectName << std::endl;
    return nullptr;
}

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
        name.append(std::to_string(mCounter++).c_str());
        if (type == "Gold")
        {
            return new GoldObject(name, description, minValue, ObjectType::Gold, mCounter++);
        }
        else if (type == "Weapon")
        {
            return new WeaponObject(name, description, minValue, maxValue, ObjectType::Weapon, mCounter++);
        }
        else if (type == "Armor")
        {
            return new ArmorObject(name, description, protection, ObjectType::Armor, mCounter++);
        }
        else if (type == "Consumable_Health" || type == "Consumable_Experience" || type == "Consumable_Teleport")
        {
            ObjectType consumableType;
            if (type == "Consumable_Health")
                consumableType = ObjectType::Consumable_Health;
            else if (type == "Consumable_Experience")
                consumableType = ObjectType::Consumable_Experience;
            else
                consumableType = ObjectType::Consumable_Teleport;

            return new ConsumableObject(name, description, minValue, maxValue, consumableType, mCounter++);
        }
    }

    std::cerr << "Object not found in database" << std::endl;
    return nullptr;
}