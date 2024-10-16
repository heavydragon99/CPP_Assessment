#include "Player.h"

#include <iostream>
#include <stdexcept>

Player::Player()
    : mHealth(20), mAttackPercentage(40), mGold(0), mGodMode(false), mEquippedWeapon(nullptr), mEquippedArmor(nullptr)
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
        item.printName();
        item.printDescription();
        std::cout << std::endl;
    }
    std::cout << "Godmode: " << (mGodMode ? "Ja" : "Nee") << std::endl;
}

std::unique_ptr<GameObjectFacade> Player::equipObject(const char *aItem)
{
    std::unique_ptr<GameObjectFacade> previousItem = nullptr;

    for (auto it = mInventory.begin(); it != mInventory.end(); ++it)
    {
        if (it->getName() == aItem)
        {
            if (it->getType() == ObjectType::Weapon)
            {
                if (mEquippedWeapon && mEquippedWeapon->getName() == aItem)
                {
                    previousItem = std::make_unique<GameObjectFacade>(std::move(*mEquippedWeapon));
                    mInventory.erase(it);
                }
                mEquippedWeapon = &(*it);
                std::cout << "Wapen uitgerust: " << aItem << std::endl;
            }
            else if (it->getType() == ObjectType::Armor)
            {
                if (mEquippedArmor && mEquippedArmor->getName() == aItem)
                {
                    previousItem = std::make_unique<GameObjectFacade>(std::move(*mEquippedArmor));
                    mInventory.erase(it);
                }
                mEquippedArmor = &(*it);
                std::cout << "Pantser uitgerust: " << aItem << std::endl;
            }
            return previousItem;
        }
    }
    std::cout << "Item " << aItem << " niet gevonden." << std::endl;
    return nullptr;
}

void Player::consumeConsumable(const char *aConsumable)
{
    throw std::runtime_error("Not implemented");
}

void Player::addObject(GameObjectFacade&& aObject)
{
    mInventory.push_back(std::move(aObject));
}