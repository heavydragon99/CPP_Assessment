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
    std::unique_ptr<GameObjectFacade> equipObject(const char *aItem);
    void consumeConsumable(const char *aConsumable);
    void addObject(GameObjectFacade&& aObject);

private:
    std::string mName;
    int mHealth;
    int mAttackPercentage;
    std::vector<GameObjectFacade> mInventory;
    int mGold;
    GameObjectFacade* mEquippedWeapon;
    GameObjectFacade* mEquippedArmor;
    bool mGodMode;
};

#endif // PLAYER_H