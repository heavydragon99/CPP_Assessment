#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Sean.h"
#include "DungeonFacade.h"

#include <memory>

enum class PlayerAction
{
    Kijk,
    Zoek,
    Ga,
    Pak,
    Leg,
    Bekijk,
    Sla,
    Draag,
    Wacht,
    Consumeer,
    Help,
    Godmode,
    Quit,
    Invalid
};

class Game
{
public:
    // Constructors
    Game() = default;

    // Destructor
    virtual ~Game() = default;

    // Methods
    void run();

private:
    // Private Methods
    void initialize();
    void loadDungeon();
    void generateDungeon();
    void printCurrentLocation() const;
    void printCurrentSetting() const;
    void playerInput();
    PlayerAction getPlayerAction(const std::string &aInput) const;
    void updateDungeon();

    void lookAction();
    void searchAction();
    void goAction(const std::string &aDirection);
    void takeAction(const std::string &aObject);
    void dropAction(const std::string &aObject);
    void examineAction(const std::string &aObject);
    void hitAction(const std::string &aTarget);
    void wearAction(const std::string &aObject);
    void waitAction();
    void consumeAction(const std::string &aObject);
    void helpAction() const;
    void godmodeAction();

    void endGame();

private:
    // Members
    std::unique_ptr<Player> mPlayer;
    std::unique_ptr<DungeonFacade> mDungeon;

    inline static const std::string StartingWeapon{"dolk"};

    bool mQuit;
};

#endif // GAME_H