//
// Created by elobo on 10/12/2025.
//
#include "gameConsole.h"
#include "../Joueurs/playerConsole.h"

GameConsole* GameConsole::instanceConsole = nullptr;

void GameConsole::addEachPlayerToGame() {
    cout << "Start of the game ! \n";
    for (size_t i = 0; i < nb_players; i++) {
        cout << "Name of player " << to_string(i) << " :";
        string name;
        cin >> name;
        addPlayer(name);
    }
}
void GameConsole::displayCurrentPlayerInfo() {
    cout << "Current player : " << *players.at(current_player);
}
void GameConsole::actionsPlayer(Amalena::River* river_copy,BoardManager* board_copy) {
    cout << "Do you want to abandon the game ? (Y/N): ";
    string answer;
    cin >> answer;
    if (answer == "Y") {
        abandonGame();
        freeInstance();
        return;
    }
    char satisfied_player = 'N';
    char option = 'A';
    Tile* tile = nullptr;
    do {
        tile = &pickRiver();
        players.at(current_player)->playTurn(*tile);

        cout << "Are you satisfied ? (Y/N): ";
        cin >> satisfied_player;

        while (satisfied_player == 'N') {
            players.at(current_player)->setBoard(*board_copy);
            cout << "Your board : \n" << players.at(current_player)->getBoard();
            cout << "Pick another tile (A) or choose another place (B)?: ";
            cin >> option;
            if (option == 'A') {
                Amalena::River* temp_river = new Amalena::River(*river_copy);
                *river = *temp_river;
                tile = &pickRiver();
                delete temp_river;
            }
            players.at(current_player)->playTurn(*tile);
            cout << "Are you satisfied now ? (Y/N): ";
            cin >> satisfied_player;
        }

    } while (satisfied_player == 'N');
}

void GameConsole::addPlayer(const string& name) {
    if (nb_players == nb_players_max)
    {
        //Put an exception instead
        cout << "Can't add an additionnal player, you have reached the maximum.";
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
    cout << "Write the position of the tile you want (first tile at position 1) : ";
    int position = 0;
    cin >> position;
    while (players[current_player]->getStones() < position - 1) {
        cout << "You don't have enough stones, select another position : ";
        cin >> position;
    }
    Tile& chosen_tile = river->giveTile(position);
    size_t newStones = players[current_player]->getStones() - (position - 1);
    players[current_player]->setStones(newStones);
    return chosen_tile;
}

void GameConsole::askNameSoloGame(){
    cout << "Start of the solo game ! \n";
    cout << "What is your name ? :";
    string name;
    cin >> name;
    addPlayer(name);
}

void GameConsole::architectCreation(int difficulty) {
    Player* architect = new ArchitectConsole("Architect", difficulty);
    players.push_back(architect);
}
void GameConsole::architectPlaySoloGame(){
    cout << "Architect's turn!\n";
    cout << "Stones : " << players.at(current_player)->getStones() << "\n";
    Tile* chosen_tile_ptr = nullptr;
    int chosen_pos = 1;
    int pos = 1;
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
    if (!chosen_tile_ptr || (chosen_pos - 1) > players.at(current_player)->getStones()) {
        chosen_tile_ptr = &*river->begin();
        chosen_pos = 1;
    }
    if (chosen_tile_ptr) {
        cout << "Architect took the tile " << chosen_pos << "\n";
        river->giveTile(chosen_pos);
        players.at(1)->addStones(-chosen_pos);
        players.at(1)->playTurn(*chosen_tile_ptr);
    } else {
        cout << "Architect can't play.\n";
    }
}
void GameConsole::realPlayerPlaySoloGame(BoardManager* board_copy,Amalena::River* river_copy){
    cout << "Your turn !" << "\n";
    cout << *players.at(current_player) << "\n";
    int stones_before = players.at(0)->getStones();
    int architect_stones_before = players.at(1)->getStones();
    char satisfied_player = 'N';
    char option = 'A';
    do {
        Tile* tile = &pickRiver();
        int stones_after = players.at(0)->getStones();
        int stones_lost = stones_before - stones_after;
        players.at(1)->addStones(stones_lost);
        players.at(0)->playTurn(*tile);
        cout << "Are you satisfied with your move? (Y/N) : ";
        cin >> satisfied_player;
        if (satisfied_player == 'N') {
            players.at(0)->setBoard(*board_copy);
            players.at(0)->setStones(stones_before);
            players.at(1)->setStones(architect_stones_before);
            cout << "Pick another tile (A) or choose a new place (B)? ";
            do { cin >> option; } while(option != 'A' && option != 'B');
            if (option == 'A') {
                Amalena::River* temp_river = new Amalena::River(*river_copy);
                *river = *temp_river;
                tile = &pickRiver();
                delete temp_river;
            }
            players.at(0)->playTurn(*tile);
            cout << "Are you satisfied now ? (Y/N): ";
            cin >> satisfied_player;
        }
    } while (satisfied_player == 'N');
}

string GameConsole::displayAbandonGame1() {
    cout << "Temporary abandon of the game. \n";
    cout << "Choose an id for your game : ";
    string id;
    cin >> id;
    return id;
}

void GameConsole::displayAbandonGame2(){
    cout << "Registration of game's parameters successful. \n";
}