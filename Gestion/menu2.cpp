#include <iostream>
#include "menu2.h"
#include "game.h"
using namespace std;

Menu::Menu() {
    display();
}

void Menu::display() {
    cout << "Welcome in the menu\n"
        << "What do you want to do ?\n"
        << "1. Launch a game\n"
        << "2. Resumpt a game\n"
        << "3. Display rules";
    char choice = 'A';
    cin >> choice;
    while (choice != '1' &&  choice != '2' && choice != '3') {
        switch (choice)
        {
            //erreurs sans les {} car besoin d'un "scope" local pour Game
            case '1': {
                cout << "Game parameters\n";
                cout << "Mode ? : Solo or Multi-player";
                string mode;
                cin >> mode;
                cout << "Variant ? : ";
                string variant;
                cin >> variant;
                cout << "Difficulty ? : ";
                string difficulty;
                cin >> difficulty;
                cout << "Number of players ? : 1, 2, 3 or 4";
                size_t nb_players = 0;
                cin >> nb_players;
                while (nb_players > Game::getNbPlayersMax()) {
                    cout << "Number must be < to " << Game::getNbPlayersMax() << ". Number of players ? : ";
                    cin >> nb_players;
                }
                size_t tile_count = 0;
                if (nb_players == 1 or nb_players == 2) {
                    tile_count = 60;
                }
                else if (nb_players == 3) {
                    tile_count = 75;
                }
                else if (nb_players == 4) {
                    tile_count = 90;
                }
                Game& game = Game::giveInstance(tile_count, variant, mode, difficulty, nb_players);
                game.informationsGame();
                //game.manageGame();
                break;
            }
            case '2':
                cout << "Game resumption.\n";
                break;
            case '3':
                cout << "Here are the rules of the game :\n"
                    "In this tile-laying game, players take on the role of architects who compete against each other "
                    "by each creating a city using city tiles. Each city tile is composed of 3 "
                    "construction hexagons, each hexagon representing a neighbourhood, a square or a quarry. "
                    "There are several types of neighbourhood. Each neighbourhood earns victory points "
                    "if they are correctly placed according to their type.";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }
}
