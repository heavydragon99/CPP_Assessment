#include "Game.h"

#include "XmlReader.h"
#include "GameObjectFacade.h"

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
    auto dolk = std::unique_ptr<GameObject>(mDungeon->getGameObject(StartingWeapon.c_str()));
    GameObjectFacade dolkFacade(std::move(dolk));
    mPlayer->addObject(std::move(dolkFacade));
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
    printCurrentSetting();

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
    throw std::runtime_error("Actie 'Kijk' is nog niet geïmplementeerd.");
}

void Game::searchAction()
{
    mDungeon->update();
    throw std::runtime_error("Actie 'Zoek' is nog niet geïmplementeerd.");
}

void Game::goAction(const std::string &aDirection)
{
    mDungeon->update();
    throw std::runtime_error("Actie 'Ga' is nog niet geïmplementeerd.");
}

void Game::takeAction(const std::string &aObject)
{
    throw std::runtime_error("Actie 'Pak' is nog niet geïmplementeerd.");
}

void Game::dropAction(const std::string &aObject)
{
    throw std::runtime_error("Actie 'Leg' is nog niet geïmplementeerd.");
}

void Game::examineAction(const std::string &aObject)
{
    throw std::runtime_error("Actie 'Bekijk' is nog niet geïmplementeerd.");
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
        mDungeon->placeObject(std::move(previousItem));
    }
    mDungeon->update();
}

void Game::waitAction()
{
    mDungeon->update();
    throw std::runtime_error("Actie 'Wacht' is nog niet geïmplementeerd.");
}

void Game::consumeAction(const std::string &aObject)
{
    throw std::runtime_error("Actie 'Consumeer' is nog niet geïmplementeerd.");
}

void Game::helpAction()
{
    std::cout << "Beschikbare acties:" << std::endl;
    std::cout << "Kijk - Om je heen kijken" << std::endl;
    std::cout << "Zoek - Zoeken in de omgeving" << std::endl;
    std::cout << "Ga <noord|oost|zuid|west> - Naar een andere locatie gaan" << std::endl;
    std::cout << "Pak <item> - Een object oppakken" << std::endl;
    std::cout << "Leg <item> - Een object neerleggen" << std::endl;
    std::cout << "Bekijk <object> - Een object bekijken" << std::endl;
    std::cout << "Bekijk <vijand> - Een vijand bekijken" << std::endl;
    std::cout << "Bekijk - Jezelf bekijken" << std::endl;
    std::cout << "Sla <vijand> - Een vijand aanvallen" << std::endl;
    std::cout << "Draag <object> - Een object dragen" << std::endl;
    std::cout << "Wacht - Wachten" << std::endl;
    std::cout << "Consumeer <object> - Een object consumeren" << std::endl;
    std::cout << "Help - Deze helptekst tonen" << std::endl;
    std::cout << "Godmode - Godmode activeren" << std::endl;
    std::cout << "Quit - Het spel verlaten" << std::endl;
}

void Game::godmodeAction()
{
    throw std::runtime_error("Actie 'Godmode' is nog niet geïmplementeerd.");
}