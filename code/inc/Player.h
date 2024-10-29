#ifndef PLAYER_H
#define PLAYER_H

#include "IGameObject.h"

#include <string>
#include <vector>
#include <memory>

class Player
{
public:
    // Constructors
    Player();
    virtual ~Player() = default;

    // Assignment Operators
    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;
    Player(Player &&) noexcept = default;
    Player &operator=(Player &&) noexcept = default;

    // Methods
    void printDescription() const;
    std::unique_ptr<IGameObject> equipObject(const char *aItem);
    void removeEquippedItem(IGameObject* equippedItem);
    void addHealth(int aHealth);
    void addExperience(int aExperience);
    void addObject(std::unique_ptr<IGameObject> aObject);
    bool printObject(const char *aObjectName) const;
    std::unique_ptr<IGameObject> dropObject(const char *aObjectName);
    void toggleGodMode();
    std::vector<std::unique_ptr<IGameObject>> &getInventory();
    int getHealth() const;
    int getAttackPercentage() const;
    int getAttackDamage() const;
    bool isDead() const;
    int getGold() const;
    std::string getName() const;

private:
    // Private Methods

private:
    // Members
    std::string mName;
    int mHealth;
    int mAttackPercentage;
    std::vector<std::unique_ptr<IGameObject>> mInventory;
    int mGold;
    IGameObject *mEquippedWeapon;
    IGameObject *mEquippedArmor;
    bool mGodMode;
};

#endif // PLAYER_H