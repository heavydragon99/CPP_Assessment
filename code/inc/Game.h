#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Sean.h"
#include "DungeonFacade.h"

#include <memory>

class Game
{
public: // public functions
    Game();
    virtual ~Game() = default;
    void run();

private: // private functions
    void initialize();
    void loadDungeon();
    void generateDungeon();

private: // private variables
    std::unique_ptr<Player> mPlayer;
    std::unique_ptr<DungeonFacade> mDungeon;
};

#endif // GAME_H