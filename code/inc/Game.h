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
public: // public functions
    Game() = default;
    virtual ~Game() = default;
    void run();

private: // private functions
    void initialize();
    void loadDungeon();
    void generateDungeon();
    void printCurrentLocation();
    void printCurrentSetting();
    void playerInput();
    PlayerAction getPlayerAction(const std::string &aInput);
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
    void helpAction();
    void godmodeAction();

    void endGame();

private: // private variables
    std::unique_ptr<Player> mPlayer;
    std::unique_ptr<DungeonFacade> mDungeon;

    inline static const std::string StartingWeapon{"dolk"};

    bool mQuit;
};

#endif // GAME_H