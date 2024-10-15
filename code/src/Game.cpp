#include "Game.h"

#include "XmlReader.h"
#include "GameObjectFacade.h"

#include <iostream>
#include <string>

Game::Game()
{
    mDungeon = std::make_unique<DungeonFacade>();
}

void Game::run()
{
    initialize();
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

    mPlayer = std::make_unique<Player>();
    auto dolk = std::unique_ptr<GameObject>(mDungeon->getGameObject(StartingWeapon.c_str()));
    auto dolkFacade = std::make_unique<GameObjectFacade>(*dolk);
    mPlayer->addObject(std::move(dolkFacade));
    mPlayer->equipWeapon(StartingWeapon.c_str());

    printCurrentSetting();
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
            path = "xml/kasteelruine.xml"; // Assuming "default.xml" is the standard XML file
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
    mPlayer->printDescription();
}