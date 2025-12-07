//
// Created by elobo on 02/12/2025.
//

//
// Created by elobo on 20/11/2025.
//

#include "game.h"
#include "../Chantier/river.h"
#include <iostream>
#include <vector>
#include "../Tuiles/deck.h"
#include "../Joueurs/player.h"

using namespace Eloise;

//static attributs
Game* Game::instance = nullptr;
size_t Game::nb_players_max = 4;

Game::Game(size_t nb_players) :
nb_players(nb_players),
deck(new Eloise::Deck(nb_players)),
pile(new Amalena::Pile(*deck)),
river(new Amalena::River(nb_players+2,*pile))
{
}

//free of players, river, pile, deck
//think of saving of information in order to resume games
Game::~Game(){
    for (auto& p: players) {
        delete p;
    }
    delete river;
    delete pile;
    delete deck;
}

void Game::displayPlayers() {
    for (auto player : players) {
        cout << player->getName() << "\n";
    }
}

void Game::addPlayer(const string& name) {
    if (nb_players == nb_players_max)
    {
        //Put an exception instead
        cout << "Can't add an additionnal player, you have reached the maximum.";
    }
    else {
        Player* p = new Player(name);
        players.push_back(p);
    }
}

Player* Game::getPlayer(size_t position) {
    if (position < nb_players) {
        return players.at(position);
    }
    else {
        //Put an exception instead
        cout << "Invalid position.";
        return nullptr;
    }
}

void Game::nextPlayer() {
    current_player++;
    current_player %= nb_players;
}

Tile& Game::pickRiver() {
    //diplaying of river and the position of the tiles
    cout << *river;
    //player says that he wants a tile at a certain position
    cout << "\n";
    cout << "Write the position of the tile you want (first tile at position 1) : ";
    int position = 0;
    cin >> position;
    //getStones() to acknowledge if he can buy the tile ==> loop while player.getStones() < position
    while (players[current_player]->getStones() < position - 1) {
        cout << "You don't have enough stones, select another position : ";
        cin >> position;
    }
    //player actually picks the tile in the river using river.giveTile()
    Barnabe::Tile& chosen_tile = river->giveTile(position);
    //setStones() to modify the amont of stones he's got left
    players[current_player]->setStones(players[current_player]->getStones() - (position - 1));
    return chosen_tile;
}

//mode multi-player
void Game::manageGame() {
    cout << "Start of the game ! \n";
    for (size_t i = 0; i < nb_players; i++) {
        cout << "Name of player " << to_string(i) << " :";
        string name;
        cin >> name;
        addPlayer(name);
    }

    while (!(river->stay1() && pile->isEmpty())) {
        cout << "Current player : " << *players.at(current_player);
        char satisfied_player = 'N';
        char option = 'A';
        Tile* tile = nullptr;

        Amalena::River* river_copy = new Amalena::River(*river);
        BoardManager* board_copy = new BoardManager(players.at(current_player)->getBoard());

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
                    river = temp_river;
                    tile = &pickRiver();
                    delete temp_river;
                }
                players.at(current_player)->playTurn(*tile);
                cout << "Are you satisfied now ? (Y/N): ";
                cin >> satisfied_player;
            }

        } while (satisfied_player == 'N');

        delete river_copy;
        delete board_copy;
        nextPlayer();
    }
}


//mode solo :
void Game::manageSoloGame(int difficulty) {
    cout << "Start of the solo game ! \n";
    cout << "What is your name ? :";
    string name;
    cin >> name;
    addPlayer(name);

    Player* architect = new Architect("Architect", difficulty);
    players.push_back(architect);

    while (!(river->stay1() && pile->isEmpty())) {
        if (current_player != 0) {
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
            nextPlayer();
        }
        else {
            cout << "Your turn !" << "\n";
            cout << *players.at(current_player) << "\n";

            int stones_before = players.at(0)->getStones();
            int architect_stones_before = players.at(1)->getStones();
            char satisfied_player = 'N';
            char option = 'A';
            Tile* tile = nullptr;
            BoardManager* board_copy = new BoardManager(players.at(0)->getBoard());
            Amalena::River* river_copy = new Amalena::River(*river);
            do {
                tile = &pickRiver();
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
                        river = temp_river;
                        tile = &pickRiver();
                        delete temp_river;
                    }
                    players.at(0)->playTurn(*tile);
                    cout << "Are you satisfied now ? (Y/N): ";
                    cin >> satisfied_player;
                }
            } while (satisfied_player == 'N');
            delete river_copy;
            delete board_copy;
            nextPlayer();
        }
    }
}


void Game::endGame() {
    //displaying of each player's score thanks to method of Player
}