#ifndef PLAYER_H
#define PLAYER_H

#include "IGameObject.h"

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
    std::unique_ptr<IGameObject> equipObject(const char *aItem);
    void consumeConsumable(const char *aConsumable);
    void addObject(std::unique_ptr<IGameObject> aObject);
    bool printObject(const char *aObjectName);

private:
    std::string mName;
    int mHealth;
    int mAttackPercentage;
    std::vector<std::unique_ptr<IGameObject>> mInventory;
    int mGold;
    IGameObject* mEquippedWeapon;
    IGameObject* mEquippedArmor;
    bool mGodMode;
};

#endif // PLAYER_H