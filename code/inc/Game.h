#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Sean.h"
#include "DungeonFacade.h"

#include <memory>

/**
 * @brief Enum class representing possible actions a player can take.
 */
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

/**
 * @brief The Game class manages the main game loop and player interactions.
 */
class Game
{
public:
    // Constructors
    /**
     * @brief Default constructor for Game.
     */
    Game() = default;

    // Destructor
    /**
     * @brief Destructor for Game.
     */
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
    /**
     * @brief Unique pointer to the Player object.
     */
    std::unique_ptr<Player> mPlayer;

    /**
     * @brief Unique pointer to the DungeonFacade object.
     */
    std::unique_ptr<DungeonFacade> mDungeon;

    /**
     * @brief The starting weapon for the player.
     */
    inline static const std::string StartingWeapon{"dolk"};

    /**
     * @brief Flag indicating whether the game should quit.
     */
    bool mQuit;
};

#endif // GAME_H