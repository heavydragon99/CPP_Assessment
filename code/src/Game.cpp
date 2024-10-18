#include "Game.h"

#include "XmlReader.h"
#include "IGameObject.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <limits>

// Function to clear the console
void clearConsole()
{
    std::cout << "\033[2J\033[1;1H";
}

Game::Game()
{
    mDungeon = std::make_unique<DungeonFacade>();
}

void Game::run()
{
    clearConsole();
    initialize();
    clearConsole();
    printCurrentSetting();
    bool quit = false;
    while (!quit)
    {
        playerInput(&quit);
    }
    clearConsole();
}

void Game::initialize()
{
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
    mPlayer->addObject(std::move(dolk));
    mPlayer->equipObject(StartingWeapon.c_str());
}

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
    auto locations = xmlReader.getLocations();

    mDungeon->createDungeon(locations);
}

void Game::generateDungeon()
{
    int locations;
    std::cout << "Geeft aantal locaties op: ";
    std::cin >> locations;

    mDungeon->generateDungeon(locations);
}

void Game::printCurrentLocation()
{
    mDungeon->printShortDescription();
}

void Game::printCurrentSetting()
{
    mDungeon->printLongDescription();
}

void Game::playerInput(bool *aQuit)
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
    printCurrentLocation();

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
            *aQuit = true;
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

PlayerAction Game::getPlayerAction(const std::string &aAction)
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

void Game::lookAction()
{
    clearConsole();
    printCurrentSetting();
}

void Game::searchAction()
{
    mDungeon->moveHiddenObjects();
    mDungeon->update();
    throw std::runtime_error("Actie 'Zoek' is nog niet geïmplementeerd.");
}

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
    if (mDungeon->moveLocation(direction))
    {
        // mDungeon->update(); // Only update if the location was moved
        clearConsole();
        printCurrentLocation();
    }
}

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

void Game::dropAction(const std::string &aObject)
{
    auto item = mPlayer->dropObject(aObject.c_str());
    if (item)
    {
        mDungeon->placeObject(std::move(item));
    }
    else{
        std::cout << "Object " << aObject << " niet gevonden in je inventory" << std::endl;
    }

}

void Game::examineAction(const std::string &aObject)
{
    if (aObject.empty())
    {
        mPlayer->printDescription();
        return;
    }
    if (mPlayer->printObject(aObject.c_str()))
    {
        return;
    }
    if (!mDungeon->printGameObject(aObject.c_str()))
    {
        std::cout << "Object " << aObject << " niet gevonden" << std::endl;
    }
}

void Game::hitAction(const std::string &aTarget)
{
    mDungeon->update();
    throw std::runtime_error("Actie 'Sla' is nog niet geïmplementeerd.");
}

void Game::wearAction(const std::string &aObject)
{
    auto previousItem = mPlayer->equipObject(aObject.c_str());
    if (previousItem)
    {
        if (mDungeon->placeObject(std::move(previousItem)))
        {
            mDungeon->update(); // Only update if the object was placed in the dungeon
        }
    }
}

void Game::waitAction()
{
    mDungeon->update();
}

void Game::consumeAction(const std::string &aObject)
{
    throw std::runtime_error("Actie 'Consumeer' is nog niet geïmplementeerd.");
}

void Game::helpAction()
{
    std::cout << "Beschikbare acties:" << std::endl;
    std::cout << "kijk - Om je heen kijken" << std::endl;
    std::cout << "zoek - Zoeken in de omgeving" << std::endl;
    std::cout << "ga <noord|oost|zuid|west> - Naar een andere locatie gaan" << std::endl;
    std::cout << "pak <item> - Een object oppakken" << std::endl;
    std::cout << "leg <item> - Een object neerleggen" << std::endl;
    std::cout << "bekijk <object> - Een object bekijken" << std::endl;
    std::cout << "bekijk <vijand> - Een vijand bekijken" << std::endl;
    std::cout << "bekijk - Jezelf bekijken" << std::endl;
    std::cout << "sla <vijand> - Een vijand aanvallen" << std::endl;
    std::cout << "draag <object> - Een object dragen" << std::endl;
    std::cout << "wacht - Wachten" << std::endl;
    std::cout << "consumeer <object> - Een object consumeren" << std::endl;
    std::cout << "help - Deze helptekst tonen" << std::endl;
    std::cout << "godmode - Godmode toggelen" << std::endl;
    std::cout << "quit - Het spel verlaten" << std::endl;
}

void Game::godmodeAction()
{
    throw std::runtime_error("Actie 'Godmode' is nog niet geïmplementeerd.");
}