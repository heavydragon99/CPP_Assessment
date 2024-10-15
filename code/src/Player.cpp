#include "Player.h"

#include <iostream>
#include <stdexcept>

Player::Player()
    : mHealth(20), mAttackPercentage(40), mGold(0), mGodMode(false)
{
    std::cout << "Wat is je naam? ";
    std::cin >> mName;
}

void Player::printDescription()
{
    std::cout << "Naam: " << mName << std::endl;
    std::cout << "Levenspunten: " << mHealth << std::endl;
    std::cout << "Aanvalskans: " << mAttackPercentage << "%" << std::endl;
    std::cout << "Goud: " << mGold << std::endl;
    //print equipped weapon
    std::cout << "Uitgeruste wapen: ";
    if (mEquippedWeapon)
    {
        mEquippedWeapon->printName();
        mEquippedWeapon->printDescription();
    }
    else
    {
        std::cout << "Geen" << std::endl;
    }

    //print equipped armor
    std::cout << "Uitgeruste pantser: ";
    if (mEquippedArmor)
    {
        mEquippedArmor->printName();
        mEquippedArmor->printDescription();
    }
    else
    {
        std::cout << "Geen" << std::endl;
    }

    //print inventory
    std::cout << "Inventaris: " << std::endl;
    for (auto &item : mInventory)
    {
        item->printName();
        item->printDescription();
        std::cout << std::endl;
    }
    std::cout << "Godmode: " << (mGodMode ? "Ja" : "Nee") << std::endl;
}

void Player::equipWeapon(const char *aItem)
{
    for (auto it = mInventory.begin(); it != mInventory.end(); ++it)
    {
        if ((*it)->getType() == ObjectType::Weapon && (*it)->getName() == aItem)
        {
            mEquippedWeapon = std::move(*it);
            mInventory.erase(it);
            return;
        }
    }
    std::cout << "Item niet gevonden." << std::endl;
}

void Player::equipArmor(const char *aItem)
{
    for (auto it = mInventory.begin(); it != mInventory.end(); ++it)
    {
        if ((*it)->getType() == ObjectType::Armor && (*it)->getName() == aItem)
        {
            mEquippedArmor = std::move(*it);
            mInventory.erase(it);
            return;
        }
    }
    std::cout << "Item niet gevonden." << std::endl;
}

void Player::consumeConsumable(const char *aConsumable)
{
    throw std::runtime_error("Not implemented");
}

void Player::addObject(std::unique_ptr<GameObjectFacade> aObject)
{
    mInventory.push_back(std::move(aObject));
}