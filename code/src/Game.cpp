#include "Game.h"

#include "XmlReader.h"
#include "IGameObject.h"
#include "SqlReader.h"

#include "LocationFactory.h"
#include "GameObjectFactory.h"
#include "EnemyFactory.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <limits>
#include <utility>

/**
 * @brief Clears the console screen.
 */
void clearConsole()
{
    std::cout << "\033[2J\033[1;1H";
}

// Methods

/**
 * @brief Runs the main game loop.
 */
void Game::run()
{
    clearConsole();
    initialize();
    clearConsole();
    printCurrentSetting();
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (!mQuit)
    {
        playerInput();
    }
    clearConsole();
}

/**
 * @brief Initializes the game by setting up the dungeon and player.
 */
void Game::initialize()
{
    LocationFactory locationFactory;
    locationFactory.resetCounter();
    GameObjectFactory gameObjectFactory;
    gameObjectFactory.resetCounter();
    EnemyFactory enemyFactory;
    enemyFactory.resetCounter();

    mQuit = false;
    mDungeon = std::make_unique<DungeonFacade>();
    std::string choice;
    while (true)
    {
        std::cout << "Wilt u een kerker laden of genereren? (laden/genereren): ";
        std::cin >> choice;

        if (choice == "laden")
        {
            loadDungeon();
            break;
        }
        else if (choice == "genereren")
        {
            generateDungeon();
            break;
        }
        else
        {
            std::cout << "Ongeldige keuze. Probeer het opnieuw." << std::endl;
        }
    }
    clearConsole();

    mPlayer = std::make_unique<Player>();
    auto dolk = std::unique_ptr<IGameObject>(mDungeon->createGameObject(StartingWeapon.c_str()));
    std::string weaponName = dolk->getName().c_str();
    mPlayer->addObject(std::move(dolk));
    mPlayer->equipObject(weaponName.c_str());
}

/**
 * @brief Loads the dungeon from an XML file.
 */
void Game::loadDungeon()
{
    std::string xmlChoice;
    std::string path;
    while (true)
    {
        std::cout << "Wilt u een standaard XML-bestand laden of een eigen XML-bestand? (standaard/eigen): ";
        std::cin >> xmlChoice;

        if (xmlChoice == "standaard")
        {
            path = "/home/sean/school_stuff/leerjaar_4/minor/cpp/assessment-cplus-24-25-heavydragon99/xml/kasteelruine.xml"; // Assuming "default.xml" is the standard XML file
            break;
        }
        else if (xmlChoice == "eigen")
        {
            std::cout << "Geef het pad naar het bestand: ";
            std::cin >> path;
            break;
        }
        else
        {
            std::cout << "Ongeldige keuze. Probeer het opnieuw." << std::endl;
        }
    }

    XmlReader xmlReader(path.c_str());
    std::vector<Sean::ParsedLocations> locations = xmlReader.getLocations();

    mDungeon->createDungeon(locations);
}

/**
 * @brief Generates a random dungeon.
 */
void Game::generateDungeon()
{
    int locations;
    while (true)
    {
        std::cout << "Geeft aantal locaties op (1-20): ";
        std::cin >> locations;

        if (std::cin.fail() || locations <= 0 || locations > 20)
        {
            std::cin.clear();                                                   // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Ongeldige invoer. Probeer het opnieuw." << std::endl;
        }
        else
        {
            break;
        }
    }

    try
    {
        mDungeon->generateDungeon(locations);
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
}

/**
 * @brief Prints the short description of the current location.
 */
void Game::printCurrentLocation() const
{
    mDungeon->printShortDescription();
}

/**
 * @brief Prints the long description of the current setting.
 */
void Game::printCurrentSetting() const
{
    mDungeon->printLongDescription();
}

/**
 * @brief Handles player input and executes the corresponding actions.
 */
void Game::playerInput()
{
    std::string input;

    std::cout << "Voer een actie in: ";
    std::getline(std::cin, input);

    size_t spacePos = input.find(' ');
    std::string action = input.substr(0, spacePos);
    std::string argument = (spacePos == std::string::npos) ? "" : input.substr(spacePos + 1);

    if (!argument.empty() && argument[0] == ' ')
    {
        argument = argument.substr(1);
    }
    clearConsole();

    try
    {
        switch (getPlayerAction(action))
        {
        case PlayerAction::Kijk:
            lookAction();
            break;
        case PlayerAction::Zoek:
            searchAction();
            break;
        case PlayerAction::Ga:
            goAction(argument);
            break;
        case PlayerAction::Pak:
            takeAction(argument);
            break;
        case PlayerAction::Leg:
            dropAction(argument);
            break;
        case PlayerAction::Bekijk:
            examineAction(argument);
            break;
        case PlayerAction::Sla:
            hitAction(argument);
            break;
        case PlayerAction::Draag:
            wearAction(argument);
            break;
        case PlayerAction::Wacht:
            waitAction();
            break;
        case PlayerAction::Consumeer:
            consumeAction(argument);
            break;
        case PlayerAction::Help:
            helpAction();
            break;
        case PlayerAction::Godmode:
            godmodeAction();
            break;
        case PlayerAction::Quit:
            mQuit = true;
            break;
        case PlayerAction::Invalid:
        default:
            std::cout << "Ongeldige actie. Probeer het opnieuw." << std::endl;
            break;
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * @brief Maps player input to PlayerAction enum.
 *
 * @param aAction The action input by the player.
 * @return PlayerAction The corresponding PlayerAction enum value.
 */
PlayerAction Game::getPlayerAction(const std::string &aAction) const
{
    static const std::unordered_map<std::string, PlayerAction> actionMap = {
        {"kijk", PlayerAction::Kijk},
        {"zoek", PlayerAction::Zoek},
        {"ga", PlayerAction::Ga},
        {"pak", PlayerAction::Pak},
        {"leg", PlayerAction::Leg},
        {"bekijk", PlayerAction::Bekijk},
        {"sla", PlayerAction::Sla},
        {"draag", PlayerAction::Draag},
        {"wacht", PlayerAction::Wacht},
        {"consumeer", PlayerAction::Consumeer},
        {"help", PlayerAction::Help},
        {"godmode", PlayerAction::Godmode},
        {"quit", PlayerAction::Quit}};

    auto it = actionMap.find(aAction);
    if (it != actionMap.end())
    {
        return it->second;
    }
    return PlayerAction::Invalid;
}

/**
 * @brief Updates the dungeon and applies any damage to the player.
 */
void Game::updateDungeon()
{
    int damage = mDungeon->update();
    if (damage > 0)
    {
        mPlayer->addHealth(-damage);
        std::cout << "Je hebt " << damage << " schade opgelopen en je levenspunten zijn nu " << mPlayer->getHealth() << std::endl;
    }
    if (mPlayer->isDead())
    {
        endGame();
    }
}

/**
 * @brief Executes the look action, printing the current setting.
 */
void Game::lookAction()
{
    clearConsole();
    printCurrentSetting();
}

/**
 * @brief Executes the search action, moving hidden objects and updating the dungeon.
 */
void Game::searchAction()
{
    mDungeon->moveHiddenObjects();
    updateDungeon();
}

/**
 * @brief Executes the go action, moving the player in the specified direction.
 *
 * @param aDirection The direction to move.
 */
void Game::goAction(const std::string &aDirection)
{
    Sean::Direction direction;
    if (aDirection == "noord")
    {
        direction = Sean::Direction::North;
    }
    else if (aDirection == "oost")
    {
        direction = Sean::Direction::East;
    }
    else if (aDirection == "zuid")
    {
        direction = Sean::Direction::South;
    }
    else if (aDirection == "west")
    {
        direction = Sean::Direction::West;
    }
    else
    {
        std::cout << "Ongeldige invoer" << std::endl;
        return;
    }
    if (!mDungeon->validLocation(direction))
    {
        std::cout << "Er is geen locatie in die richting" << std::endl;
        return;
    }
    else
    {
        updateDungeon();
        if (mQuit)
        {
            return;
        }
        mDungeon->moveLocation(direction);
    }
    clearConsole();
    printCurrentLocation();
}

/**
 * @brief Executes the take action, picking up the specified object.
 *
 * @param aObject The object to take.
 */
void Game::takeAction(const std::string &aObject)
{
    std::unique_ptr<IGameObject> object(mDungeon->pickUpObject(aObject.c_str()));
    if (object)
    {
        mPlayer->addObject(std::move(object));
    }
    else
    {
        std::cout << "Object " << aObject << " niet gevonden" << std::endl;
    }
}

/**
 * @brief Executes the drop action, dropping the specified object.
 *
 * @param aObject The object to drop.
 */
void Game::dropAction(const std::string &aObject)
{
    auto item = mPlayer->dropObject(aObject.c_str());
    if (item)
    {
        mDungeon->placeObject(std::move(item));
    }
    else
    {
        std::cout << "Object " << aObject << " niet gevonden in je inventory" << std::endl;
    }
}

/**
 * @brief Executes the examine action, examining the specified object or the player if no object is specified.
 *
 * @param aObject The object to examine.
 */
void Game::examineAction(const std::string &aObject)
{
    if (aObject.empty())
    {
        mPlayer->printDescription();
    }
    else if (mPlayer->printObject(aObject.c_str()))
    {
    }
    else if (!mDungeon->printGameObject(aObject.c_str()))
    {
        std::cout << "Object " << aObject << " niet gevonden" << std::endl;
    }
}

/**
 * @brief Executes the hit action, attacking the specified target.
 *
 * @param aTarget The target to hit.
 */
void Game::hitAction(const std::string &aTarget)
{
    int damage = mPlayer->getAttackDamage();
    if(damage == 0){
        std::cout << "Je hebt de vijand niet geraakt" << std::endl;
    }
    if (mDungeon->attackEnemy(aTarget.c_str(), damage))
    {
        updateDungeon();
    }
    else
    {
        std::cout << "Vijand " << aTarget << " niet gevonden" << std::endl;
    }
}

/**
 * @brief Executes the wear action, equipping the specified object.
 *
 * @param aObject The object to wear.
 */
void Game::wearAction(const std::string &aObject)
{
    auto previousItem = mPlayer->equipObject(aObject.c_str());
    if (previousItem)
    {
        if (mDungeon->placeObject(std::move(previousItem)))
        {
            updateDungeon(); // Only update if the object was placed in the dungeon
        }
    }
}

/**
 * @brief Executes the wait action, updating the dungeon.
 */
void Game::waitAction()
{
    updateDungeon();
}

/**
 * @brief Executes the consume action, consuming the specified object.
 *
 * @param aObject The object to consume.
 */
void Game::consumeAction(const std::string &aObject)
{
    for (auto iter = mPlayer->getInventory().begin(); iter != mPlayer->getInventory().end(); ++iter)
    {
        if (iter->get()->getName().c_str() == aObject)
        {
            if (iter->get()->isConsumableHealth())
            {
                mPlayer->addHealth(iter->get()->getValue());
                std::cout << "Je hebt " << aObject << " geconsumeerd en je levenspunten zijn nu " << mPlayer->getHealth() << std::endl;
                mPlayer->getInventory().erase(iter);
                return;
            }
            else if (iter->get()->isConsumableExperience())
            {
                mPlayer->addExperience(iter->get()->getValue());
                std::cout << "Je hebt " << aObject << " geconsumeerd en je aanvalskans is nu " << mPlayer->getAttackPercentage() << "%" << std::endl;
                mPlayer->getInventory().erase(iter);
                return;
            }
            else if (iter->get()->isConsumableTeleport())
            {
                mDungeon->teleport(iter->get()->getValue());
                std::cout << "Je hebt " << aObject << " geconsumeerd en je bent geteleporteerd naar een andere locatie" << std::endl;
                mPlayer->getInventory().erase(iter);
                return;
            }else{
                std::cout << "Je kunt " << aObject << " niet consumeren" << std::endl;
                return;
            }
        }
    }
    std::cout << "Object " << aObject << " niet gevonden in je inventory" << std::endl;
}

/**
 * @brief Executes the help action, displaying available commands.
 */
void Game::helpAction() const
{
    std::cout << "Beschikbare acties:" << std::endl;
    std::cout << "kijk - Om je heen kijken" << std::endl;
    std::cout << "zoek* - Zoeken in de omgeving" << std::endl;
    std::cout << "ga* <noord|oost|zuid|west> - Naar een andere locatie gaan" << std::endl;
    std::cout << "pak <item> - Een object oppakken" << std::endl;
    std::cout << "leg <item> - Een object neerleggen" << std::endl;
    std::cout << "bekijk <object> - Een object bekijken" << std::endl;
    std::cout << "bekijk <vijand> - Een vijand bekijken" << std::endl;
    std::cout << "bekijk - Jezelf bekijken" << std::endl;
    std::cout << "sla* <vijand> - Een vijand aanvallen" << std::endl;
    std::cout << "draag* <object> - Een object dragen" << std::endl;
    std::cout << "wacht* - Wachten" << std::endl;
    std::cout << "consumeer <object> - Een object consumeren" << std::endl;
    std::cout << "help - Deze helptekst tonen" << std::endl;
    std::cout << "godmode - Godmode toggelen" << std::endl;
    std::cout << "quit - Het spel verlaten" << std::endl;
}

/**
 * @brief Toggles god mode for the player.
 */
void Game::godmodeAction()
{
    mPlayer->toggleGodMode();
}

/**
 * @brief Ends the game, displaying the player's score and high scores.
 */
void Game::endGame()
{
    SQLReader &sqlReader = SQLReader::getInstance();
    sqlReader.putHighscore(mPlayer->getName().c_str(), mPlayer->getGold());
    std::pair<Sean::String, int> highscore[10];

    for (int i = 0; i < 10; i++)
    {
        highscore[i].first = "...";
        highscore[i].second = 0;
    }

    for (int i = 0; i < 10; i++)
    {
        if (!sqlReader.getHighscore(highscore[i].first, highscore[i].second, i + 1))
        {
            break;
        }
    }

    clearConsole();
    std::cout << "Je bent dood. Game over." << std::endl;
    std::cout << "je score is: " << mPlayer->getGold() << std::endl;
    std::cout << "Highscores:" << std::endl;
    for (int i = 0; i < 10; i++)
    {
        std::cout << "\t" << i + 1 << ". " << highscore[i].first << " - " << highscore[i].second << std::endl;
    }
    std::cout << "Bedankt voor het spelen!" << std::endl;

    std::string choice;
    while (true)
    {
        std::cout << "Wilt u opnieuw spelen of stoppen? (opnieuw/quit): ";
        std::cin >> choice;

        if (choice == "opnieuw")
        {
            mDungeon.reset();
            mPlayer.reset();
            run();
            mQuit = true;
            return;
        }
        else if (choice == "quit")
        {
            std::cout << "Het spel wordt afgesloten. Bedankt voor het spelen!" << std::endl;
            mQuit = true;
            return;
        }
        else
        {
            std::cout << "Ongeldige keuze. Probeer het opnieuw." << std::endl;
        }
    }
}