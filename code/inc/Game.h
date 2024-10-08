#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Map.h"
#include "Sean.h"

class Game
{
public: // public functions
    Game() = default;;
    virtual ~Game() = default;
    void run();

private: // private functions
    void update();
    void initialize();

private: // private variables
    Sean::UniquePtr<Player> mPlayer;
    Sean::UniquePtr<Map> mMap;
};

#endif // GAME_H