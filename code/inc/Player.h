#ifndef PLAYER_H
#define PLAYER_H

#include "GameObjectFacade.h"

#include <string>
#include <vector>
#include <memory>

class Player
{
public:
    Player();
    virtual ~Player() = default;

public:
    void printDescription();
    void equipWeapon(const char *aItem);
    void equipArmor(const char *aItem);
    void consumeConsumable(const char *aConsumable);
    void addObject(std::unique_ptr<GameObjectFacade> aObject);

private:
    std::string mName;
    int mHealth;
    int mAttackPercentage;
    std::vector<std::unique_ptr<GameObjectFacade>> mInventory;
    int mGold;
    std::unique_ptr<GameObjectFacade> mEquippedWeapon;
    std::unique_ptr<GameObjectFacade> mEquippedArmor;
    bool mGodMode;
};

#endif // PLAYER_H