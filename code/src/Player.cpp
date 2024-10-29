#include "Player.h"

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "RandomGenerator.h"

// Constructors
Player::Player()
    : mHealth(20), mAttackPercentage(40), mGold(100), mGodMode(false), mEquippedWeapon(nullptr), mEquippedArmor(nullptr)
{
    std::cout << "Wat is je naam? ";
    std::cin >> mName;
}

// Methods
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

std::unique_ptr<IGameObject> Player::equipObject(const char *aItem)
{
    std::unique_ptr<IGameObject> previousItem = nullptr;

    for (auto iter = mInventory.begin(); iter != mInventory.end(); ++iter)
    {
        if (iter->get()->getName() == aItem)
        {
            if (iter->get()->isWeapon())
            {
                if (mEquippedWeapon)
                {
                    previousItem = std::unique_ptr<IGameObject>(mEquippedWeapon->clone());
                    auto previousIter = std::find_if(mInventory.begin(), mInventory.end(), [this](const std::unique_ptr<IGameObject> &aItem)
                                                     { return aItem.get() == mEquippedWeapon; });
                    mInventory.erase(previousIter);
                }
                mEquippedWeapon = iter->get();
                std::cout << "Wapen uitgerust: " << aItem << std::endl;
            }
            else if (iter->get()->isArmor())
            {
                if (mEquippedArmor)
                {
                    previousItem = std::unique_ptr<IGameObject>(mEquippedArmor->clone());
                    auto previousIter = std::find_if(mInventory.begin(), mInventory.end(), [this](const std::unique_ptr<IGameObject> &aItem)
                                                     { return aItem.get() == mEquippedWeapon; });
                    mInventory.erase(previousIter);
                }
                mEquippedArmor = iter->get();
                std::cout << "Pantser uitgerust: " << aItem << std::endl;
            }
            return previousItem;
        }
    }
    std::cout << "Item " << aItem << " niet gevonden in je rugzak." << std::endl;
    return nullptr;
}

void Player::addHealth(int aHealth)
{
    if (mGodMode && aHealth < 0)
    {
        aHealth = 0;
    }
    mHealth += aHealth;
    // std::cout << "Je levenspunten zijn nu " << mHealth << std::endl;
}

void Player::addExperience(int aExperience)
{
    mAttackPercentage += aExperience;
    std::cout << "Je aanvalskans is nu " << mAttackPercentage << "%" << std::endl;
}

void Player::addObject(std::unique_ptr<IGameObject> aObject)
{
    if (aObject->isConsumableHealth())
    {
        mGold += aObject->getValue();
    }
    else
    {
        mInventory.push_back(std::move(aObject));
    }
}

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

void Player::toggleGodMode()
{
    mGodMode = !mGodMode;
    std::cout << "Godmode " << (mGodMode ? "geactiveerd" : "gedeactiveerd") << std::endl;
}

std::vector<std::unique_ptr<IGameObject>> &Player::getInventory()
{
    return mInventory;
}

int Player::getHealth() const
{
    return mHealth;
}

int Player::getAttackPercentage() const
{
    return mAttackPercentage;
}

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

bool Player::isDead() const
{
    return mHealth <= 0;
}

int Player::getGold() const
{
    return mGold;
}

std::string Player::getName() const
{
    return mName;
}