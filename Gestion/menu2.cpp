//
// Created by elobo on 02/12/2025.
//

#include <iostream>
#include "menu2.h"
#include "gameConsole.h"
#include "../Sauvegarde/savemanager.h"
using std::cout;

namespace Eloise {
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
                cout << "Made by Marilou, Eloïse, Amalena & Barnabé" << "\n" << "\n";
                cout << "\n=====[Main Menu]====\n"
                    << "Please choose an action : \n"
                    << "1 Launch a game\n"
                    << "2 Resume a game\n"
                    << "3 Display rules\n"
                    << ">> ";
                cin >> choice;
                switch (choice)
                {
                    //errors w/out {} because need of a local scope
                    case '1': {
                        cout << "\n== New Game ==\n";
                        cout << "-- Parameters --\n";
                        cout << "\nYou may choose to play with one or more modifiers :\n"
                                "home, market, barrack, temple, garden\nEnter 0 for disabling all.\n>> ";
                        string variant = "";
                        cin >> variant;
                        cout << "\n";
                        size_t nb_players = 0;
                        do {
                            cout << "How many players will play ? (1 to 4)\n>> ";
                            cin >> nb_players;
                        } while (nb_players > Game::getNbPlayersMax() || nb_players < 1);
                        if (nb_players == 1) {
                            GameConsole& game = GameConsole::giveInstance(nb_players+1,variant);
                            cout << "Difficulty ? (1 = easy, 2 = medium, 3 = hard)\n>>  ";
                            int difficulty = 0;
                            cin >> difficulty;
							game.setSolo(true);
							game.setDifficulty(difficulty);
                            game.manageSoloGame(difficulty);
                            game.endGame();
                        }
                        else {
                            GameConsole& game = GameConsole::giveInstance(nb_players,variant);
							game.setSolo(false);
							game.setDifficulty(0);
                            game.manageGame();
                            game.endGame();
                        }
                        GameConsole::freeInstance();
                        break;
                    }
{
    case '2':
    cout << "== Resume Game ==\n-- Setup --\n Enter game code\n>> ";
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
}