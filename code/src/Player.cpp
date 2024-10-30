#include "Player.h"

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "RandomGenerator.h"

// Constructors

/**
 * @brief Constructs a Player object with default attributes.
 */
Player::Player()
    : mHealth(20), mAttackPercentage(40), mGold(0), mGodMode(false), mEquippedWeapon(nullptr), mEquippedArmor(nullptr)
{
    std::cout << "Wat is je naam? ";
    std::cin >> mName;
}

// Methods

/**
 * @brief Prints the description of the player, including name, health, attack percentage, gold, equipped items, and inventory.
 */
void Player::printDescription() const
{
    std::cout << "Naam: " << mName << std::endl;
    std::cout << "Levenspunten: " << mHealth << std::endl;
    std::cout << "Aanvalskans: " << mAttackPercentage << "%" << std::endl;
    std::cout << "Goud: " << mGold << std::endl;
    // print equipped weapon
    std::cout << "Uitgeruste wapen: ";
    if (mEquippedWeapon)
    {
        mEquippedWeapon->printName();
    }
    else
    {
        std::cout << "Geen" << std::endl;
    }
    // print equipped armor
    std::cout << "Uitgeruste pantser: ";
    if (mEquippedArmor)
    {
        mEquippedArmor->printName();
    }
    else
    {
        std::cout << "Geen" << std::endl;
    }

    // print inventory
    std::cout << "Inventaris: " << std::endl;
    for (const auto &item : mInventory)
    {
        std::cout << "\t";
        item->printName();
    }
    std::cout << "Godmode: " << (mGodMode ? "Ja" : "Nee") << std::endl;
}

/**
 * @brief Equips an object from the player's inventory.
 * 
 * @param aItem The name of the item to equip.
 * @return std::unique_ptr<IGameObject> The previously equipped item, if any.
 */
std::unique_ptr<IGameObject> Player::equipObject(const char *aItem)
{
    std::unique_ptr<IGameObject> previousItem = nullptr;

    // Check if the item is already equipped
    if ((mEquippedWeapon && mEquippedWeapon->getName() == aItem) ||
        (mEquippedArmor && mEquippedArmor->getName() == aItem))
    {
        std::cout << "Item " << aItem << " is al uitgerust." << std::endl;
        return nullptr;
    }

    // Find item in the inventory
    auto itemIter = std::find_if(mInventory.begin(), mInventory.end(),
                                 [&](const std::unique_ptr<IGameObject> &item)
                                 {
                                     return item->getName() == aItem;
                                 });

    if (itemIter == mInventory.end())
    {
        std::cout << "Item " << aItem << " niet gevonden in je rugzak." << std::endl;
        return nullptr;
    }

    // Equip weapon or armor, replacing any currently equipped item
    auto &item = *itemIter;
    if (item->isWeapon())
    {
        if (mEquippedWeapon)
        {
            previousItem = std::unique_ptr<IGameObject>(mEquippedWeapon->clone());
            removeEquippedItem(mEquippedWeapon);
        }
        // Find item in the inventory
        auto weaponIter = std::find_if(mInventory.begin(), mInventory.end(),
                                       [&](const std::unique_ptr<IGameObject> &item)
                                       {
                                           return item->getName() == aItem;
                                       });
        auto &weapon = *weaponIter;
        mEquippedWeapon = weapon.get();
        std::cout << "Wapen uitgerust: " << aItem << std::endl;
    }
    else if (item->isArmor())
    {
        if (mEquippedArmor)
        {
            previousItem = std::unique_ptr<IGameObject>(mEquippedArmor->clone());
            removeEquippedItem(mEquippedArmor);
        }
        // Find item in the inventory
        auto armorIter = std::find_if(mInventory.begin(), mInventory.end(),
                                      [&](const std::unique_ptr<IGameObject> &item)
                                      {
                                          return item->getName() == aItem;
                                      });
        auto &armor = *armorIter;
        mEquippedArmor = armor.get();
        std::cout << "Pantser uitgerust: " << aItem << std::endl;
    }

    return previousItem;
}

/**
 * @brief Removes an equipped item from the player's inventory.
 * 
 * @param equippedItem Pointer to the equipped item to remove.
 */
void Player::removeEquippedItem(IGameObject *equippedItem)
{
    auto iter = std::find_if(mInventory.begin(), mInventory.end(),
                             [&](const std::unique_ptr<IGameObject> &item)
                             {
                                 return item.get() == equippedItem;
                             });
    if (iter != mInventory.end())
    {
        mInventory.erase(iter);
    }
}

/**
 * @brief Adds health to the player. If god mode is enabled, negative health is ignored.
 * 
 * @param aHealth The amount of health to add.
 */
void Player::addHealth(int aHealth)
{
    if (mGodMode && aHealth < 0)
    {
        aHealth = 0;
    }
    if (aHealth < 0)
    {
        if (mEquippedArmor)
        {
            aHealth += mEquippedArmor->getValue();
            if (aHealth > 0)
            {
                aHealth = 0;
            }
        }
    }
    mHealth += aHealth;
    if (mHealth < 0)
    {
        mHealth = 0;
    }
    // std::cout << "Je levenspunten zijn nu " << mHealth << std::endl;
}

/**
 * @brief Adds experience to the player, increasing the attack percentage.
 * 
 * @param aExperience The amount of experience to add.
 */
void Player::addExperience(int aExperience)
{
    mAttackPercentage += aExperience;
    std::cout << "Je aanvalskans is nu " << mAttackPercentage << "%" << std::endl;
}

/**
 * @brief Adds an object to the player's inventory. If the object is money, it increases the player's gold.
 * 
 * @param aObject The object to add.
 */
void Player::addObject(std::unique_ptr<IGameObject> aObject)
{
    if (aObject->isMoney())
    {
        mGold += aObject->getValue();
    }
    else
    {
        mInventory.push_back(std::move(aObject));
    }
}

/**
 * @brief Prints the details of an object in the player's inventory by name.
 * 
 * @param aObjectName The name of the object to print.
 * @return bool True if the object was found and printed, false otherwise.
 */
bool Player::printObject(const char *aObjectName) const
{
    for (const auto &obj : mInventory)
    {
        if (obj->getName() == aObjectName)
        {
            obj->printName();
            obj->printDescription();
            return true;
        }
    }
    return false;
}

/**
 * @brief Drops an object from the player's inventory by name.
 * 
 * @param aObjectName The name of the object to drop.
 * @return std::unique_ptr<IGameObject> The dropped object.
 */
std::unique_ptr<IGameObject> Player::dropObject(const char *aObjectName)
{
    for (auto iter = mInventory.begin(); iter != mInventory.end(); ++iter)
    {
        if (iter->get()->getName() == aObjectName)
        {
            if (mEquippedWeapon == iter->get())
            {
                mEquippedWeapon = nullptr;
            }
            if (mEquippedArmor == iter->get())
            {
                mEquippedArmor = nullptr;
            }
            std::unique_ptr<IGameObject> droppedItem = std::move(*iter);
            mInventory.erase(iter);
            return droppedItem;
        }
    }
    return nullptr;
}

/**
 * @brief Toggles god mode for the player.
 */
void Player::toggleGodMode()
{
    mGodMode = !mGodMode;
    std::cout << "Godmode " << (mGodMode ? "geactiveerd" : "gedeactiveerd") << std::endl;
}

/**
 * @brief Gets the player's inventory.
 * 
 * @return std::vector<std::unique_ptr<IGameObject>>& Reference to the vector of inventory items.
 */
std::vector<std::unique_ptr<IGameObject>> &Player::getInventory()
{
    return mInventory;
}

/**
 * @brief Gets the player's health.
 * 
 * @return int The player's health.
 */
int Player::getHealth() const
{
    return mHealth;
}

/**
 * @brief Gets the player's attack percentage.
 * 
 * @return int The player's attack percentage.
 */
int Player::getAttackPercentage() const
{
    return mAttackPercentage;
}

/**
 * @brief Gets the player's attack damage.
 * 
 * @return int The player's attack damage.
 */
int Player::getAttackDamage() const
{
    RandomGenerator randomEngine;
    if (mEquippedWeapon)
    {
        if (randomEngine.getChance(mAttackPercentage) || mGodMode)
        {
            return mEquippedWeapon->getValue();
        }
    }
    return 0;
}

/**
 * @brief Checks if the player is dead.
 * 
 * @return bool True if the player's health is less than or equal to 0, false otherwise.
 */
bool Player::isDead() const
{
    return mHealth <= 0;
}

/**
 * @brief Gets the player's gold.
 * 
 * @return int The amount of gold the player has.
 */
int Player::getGold() const
{
    return mGold;
}

/**
 * @brief Gets the player's name.
 * 
 * @return std::string The player's name.
 */
std::string Player::getName() const
{
    return mName;
}