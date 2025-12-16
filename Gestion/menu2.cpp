//
// Created by elobo on 02/12/2025.
//

#include <iostream>
#include "menu2.h"
#include "gameConsole.h"
#include "../Sauvegarde/savemanager.h"
using namespace std;
using namespace Eloise;

Menu::Menu() {
    display();
}

void Menu::display() {
    char choice = 'A';
    while (1) {
            do {
                cout << R"(        __                                   ___
       /\ \                                 /\_ \    __
   __  \ \ \/'\   _ __   ___   _____     ___\//\ \  /\_\    ____
 /'__`\ \ \ , <  /\`'__\/ __`\/\ '__`\  / __`\\ \ \ \/\ \  /',__\
/\ \L\.\_\ \ \\`\\ \ \//\ \L\ \ \ \L\ \/\ \L\ \\_\ \_\ \ \/\__, `\
\ \__/.\_\\ \_\ \_\ \_\\ \____/\ \ ,__/\ \____//\____\\ \_\/\____/
 \/__/\/_/ \/_/\/_/\/_/ \/___/  \ \ \/  \/___/ \/____/ \/_/\/___/
                                 \ \_\
                                  \/_/)" << endl;
                cout << "Marilou, Eloïse, Amalena & Barnabé" << endl << endl;
                cout << "Welcome in the menu\n"
                    << "What do you want to do ?\n"
                    << "1. Launch a game\n"
                    << "2. Resume a game\n"
                    << "3. Display rules\n"
                    << "Your answer : ";
            cin >> choice;
            switch (choice)
            {
                //errors w/out {} because need of a local scope
                case '1': {
                    cout << "Choose 0, 1 or several variants between (home - market - barrack - temple - garden)";
                    string variant = "";
                    cin >> variant;
                    cout << "Number of players ? (1, 2, 3 or 4) :";
                    size_t nb_players = 0;
                    cin >> nb_players;
                    while (nb_players > Game::getNbPlayersMax()) {
                        cout << "Number must be < to " << Game::getNbPlayersMax() << ". Number of players ? : ";
                        cin >> nb_players;
                    }
                    if (nb_players == 1) {
                        GameConsole& game = GameConsole::giveInstance(nb_players+1,variant);
                        cout << "Difficulty ? (1 = easy, 2 = medium, 3 = hard) : ";
                        int difficulty = 0;
                        cin >> difficulty;
                        game.manageSoloGame(difficulty);
                        //game.endGame();
                    }
                    else {
                        GameConsole& game = GameConsole::giveInstance(nb_players,variant);
                        game.manageGame();
                        //game.endGame();
                    }
                    GameConsole::freeInstance();
                    break;
                }
                {
                case '2':
                    cout << "Game resumption. What was the code of your game? :\n";
                    string resumption;
                    cin >> resumption;
                    Amalena::savemanager save_manager;
                    Amalena::GameMemento* game_memento = save_manager.restore(resumption);
                    //little security because instance is unique
                    GameConsole::freeInstance();
                    GameConsole& game = GameConsole::giveInstance(*game_memento);
                    game.manageResumeGame();
                    //game.endGame();
                    GameConsole::freeInstance();
                    break;
                }
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
        }while (!(choice=='1' or choice=='2' or choice=='3'));
    }
}
