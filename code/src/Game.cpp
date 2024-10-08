#include "Game.h"
#include "XmlReader.h"
#include <iostream>
#include <string>

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
}

void Game::loadDungeon()
{
    std::string path;
    std::cout << "Geef het pad naar het bestand: ";
    std::cin >> path;

    XmlReader xmlReader(path.c_str());
    auto locations = xmlReader.getLocations();

    // Process the loaded locations as needed
    std::cout << "Kerker geladen van " << path << std::endl;
}

// Placeholder for generateDungeon method
void Game::generateDungeon()
{
    std::cout << "Kerker genereren is nog niet geïmplementeerd." << std::endl;
}