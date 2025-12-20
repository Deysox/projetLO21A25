//
// Created by elobo on 10/12/2025.
//
#include "gameConsole.h"
#include "../Joueurs/playerConsole.h"

namespace Eloise {
    GameConsole* GameConsole::instanceConsole = nullptr;

    void GameConsole::addEachPlayerToGame() {
        cout << "\n-- Name Setup --\n";
        for (size_t i = 0; i < nb_players; i++) {
            cout << "Name of player " << to_string(i) << "\n>> ";
            string name;
            cin >> name;
            addPlayer(name);
        }
    }
    void GameConsole::displayCurrentPlayerInfo() {
        cout << "Current player : " << *players.at(current_player);
    }
    bool GameConsole::actionsPlayer(Amalena::River* river_copy,BoardManager* board_copy) {
        //pour abandonner et sauvegarder la partie
        cout << "Do you want to save and quit ? (Y/N)\n>> ";
        string answer;
        cin >> answer;
        if (answer == "Y") {
            abandonGame();
            return false;
        }
        else {
            char satisfied_player = 'N';
            char option = 'A';
            Tile* tile = nullptr;
            do {
                //pioche
                Tile* tile = &pickRiver();
                //placement
                players.at(current_player)->playTurn(*tile);

                cout << "Are you satisfied ? (Y/N)\n>> ";
                cin >> satisfied_player;
                //boucle tant que pas satisfait
                while (satisfied_player == 'N' || satisfied_player == 'n') {
                    //on remet le plateau à on état initial
                    players.at(current_player)->setBoard(*board_copy);
                    cout << "Your board : \n" << players.at(current_player)->getBoard();
                    //2 options de rollback
                    cout << "Pick another tile (A) or choose another place (B) ?\n>> ";
                    cin >> option;
                    if (option == 'A') {
                        //copie de copie pour ne pas perdre d'informations
                        Amalena::River* temp_river = new Amalena::River(*river_copy);
                        //rollback de la rivière
                        *river = *temp_river;
                        //nouvelle pioche
                        Tile* new_tile = &pickRiver();
                        //placement
                        players.at(current_player)->playTurn(*new_tile);
                        delete temp_river;
                    }else {
                        //nouveau placement
                        players.at(current_player)->playTurn(*tile);
                    }
                    cout << "Are you satisfied now ? (Y/N)\n>> ";
                    cin >> satisfied_player;
                }

            } while (satisfied_player == 'N' || satisfied_player == 'n');
            return true;
        }
    }

    void GameConsole::addPlayer(const string& name) {
        if (nb_players > nb_players_max)
        {
            throw MaxPlayerException();
        }
        else {
            PlayerConsole* p = new PlayerConsole(name);
            players.push_back(p);
        }
    }

    void GameConsole::displayRiver() {
        cout << *river << "\n";;
    }

    Tile& GameConsole::chooseTileRiver() {
        cout << "\nWrite the position of the tile you want (first tile at position 1)\n>> ";
        int position = 0;
        cin >> position;
        while (players[current_player]->getStones() < position - 1) {
            cout << "You don't have enough stones, please select another position\n>> ";
            cin >> position;
        }
        //appel à giveTile() qui renvoie la tuile choisie
        Tile& chosen_tile = river->giveTile(position);
        size_t newStones = players[current_player]->getStones() - (position - 1);
        players[current_player]->setStones(newStones);
        return chosen_tile;
    }

    void GameConsole::askNameSoloGame(){
        cout << "-- Solo Game -- \n";
        cout << "What is your name ?\n>>";
        string name;
        cin >> name;
        addPlayer(name);
    }

    void GameConsole::architectCreation(int difficulty) {
        Player* architect = new ArchitectConsole("Architect", difficulty);
        players.push_back(architect);
    }
    void GameConsole::architectPlaySoloGame(){
        cout << "\n-- Architect's turn --\n";
        cout << "Stones : " << players.at(current_player)->getStones() << "\n";
        //tuile choisie
        Tile* chosen_tile_ptr = nullptr;
        //sa position
        int chosen_pos = 1;
        int pos = 1;
        //boucle pour trouver la première tuile avec une PLACE
        for (auto& t : *river) {
            for (const Cell* cell : t) {
                if (cell->getType() == Type::PLACE) {
                    chosen_tile_ptr = &t;
                    chosen_pos = pos;
                    break;
                }
            }
            if (chosen_tile_ptr) break;
            ++pos;
        }
        //si pas assez de pierres ou pas de PLACE il prend la première tuile
        if (!chosen_tile_ptr || (chosen_pos - 1) > players.at(current_player)->getStones()) {
            chosen_tile_ptr = &*river->begin();
            chosen_pos = 1;
        }
        //pioche et mise à jour des pierres
        if (chosen_tile_ptr) {
            cout << "Architect took the tile " << chosen_pos << "\n\n";
            river->giveTile(chosen_pos);
            players.at(1)->addStones(-chosen_pos+1);
            players.at(1)->playTurn(*chosen_tile_ptr);
        } else {
            cout << "Architect can't play.\n";
        }
    }
    bool GameConsole::realPlayerPlaySoloGame(BoardManager* board_copy,Amalena::River* river_copy){
        cout << "Do you want to save and quit ? (Y/N)\n>> ";
        string answer;
        cin >> answer;
        //dans le cas d'un abandon, on appelle abandonGame() et on s'arrête
        if (answer == "Y") {
            abandonGame();
            return false;
        }
        else {
            cout << "\n";
            cout << *players.at(current_player) << "\n";
            //enregistrement des pierres avant pour rollback
            int stones_before = players.at(0)->getStones();
            int architect_stones_before = players.at(1)->getStones();
            char satisfied_player = 'N';
            char option = 'A';
            do {
                //pioche
                Tile* tile = &pickRiver();
                int stones_after = players.at(0)->getStones();
                int stones_lost = stones_before - stones_after;
                //on donne les pierres à l'architecte
                players.at(1)->addStones(stones_lost);
                //l'architecte joue
                players.at(0)->playTurn(*tile);
                cout << "Are you satisfied of your move? (Y/N)\n>> ";
                cin >> satisfied_player;
                if (satisfied_player == 'N' || satisfied_player == 'n') {
                    //rollback plateau
                    players.at(0)->setBoard(*board_copy);
                    cout << "Pick another tile (A) or choose a new place (B)?\n>> ";
                    do { cin >> option; } while(option != 'A' && option != 'B');
                    if (option == 'A') {
                        //rollback pierres
                        players.at(0)->setStones(stones_before);
                        players.at(1)->setStones(architect_stones_before);
                        //copie de la copie
                        Amalena::River* temp_river = new Amalena::River(*river_copy);
                        //rollback rivière
                        *river = *temp_river;
                        //nouvelle pioche
                        Tile* new_tile = &pickRiver();
                        //nouvelle affectation de pierres
                        int new_stones_after = players.at(0)->getStones();
                        int new_stones_lost = stones_before - new_stones_after;
                        players.at(1)->addStones(new_stones_lost);
                        //nouveau placement
                        players.at(0)->playTurn(*new_tile);
                        delete temp_river;
                    }
                    else {
                        //nouveau placement
                        players.at(0)->playTurn(*tile);
                    }
                    cout << "Are you satisfied now ? (Y/N)\n>> ";
                    cin >> satisfied_player;
                }
            } while (satisfied_player == 'N' || satisfied_player == 'n');
            return true;
        }
    }

    string GameConsole::displayAbandonGame1() {
        cout << "\n-- Saving -- \n";
        cout << "Please enter an ID\n>> ";
        string id;
        cin >> id;
        return id;
    }

    void GameConsole::displayAbandonGame2(){
        cout << "[SAVE] Game saved successfully \n";
    }
}