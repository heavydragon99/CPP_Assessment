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
        item->printName();
        item->printDescription();
        std::cout << std::endl;
    }
    std::cout << "Godmode: " << (mGodMode ? "Ja" : "Nee") << std::endl;
}

std::unique_ptr<IGameObject> Player::equipObject(const char *aItem)
{
    std::unique_ptr<IGameObject> previousItem = nullptr;

    for (auto it = mInventory.begin(); it != mInventory.end(); ++it)
    {
        if (it->get()->getName() == aItem)
        {
            if (it->get()->isWeapon())
            {
                if (mEquippedWeapon)
                {
                    previousItem = std::unique_ptr<IGameObject>(mEquippedWeapon->clone());
                    mInventory.erase(it);
                }
                mEquippedWeapon = it->get();
                std::cout << "Wapen uitgerust: " << aItem << std::endl;
            }
            else if (it->get()->isArmor())
            {
                if (mEquippedArmor)
                {
                    previousItem = std::unique_ptr<IGameObject>(mEquippedWeapon->clone());
                    mInventory.erase(it);
                }
                mEquippedWeapon = it->get();
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

void Player::addObject(std::unique_ptr<IGameObject> aObject)
{
    mInventory.push_back(std::move(aObject));
}