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
        cout << "Name ? :";
        string name;
        cin >> name;
        addPlayer(name);
    }
    while (!(river->stay1() && pile->isEmpty())) {
        cout << "Current player : " << *players.at(current_player);
        Tile& tile = pickRiver();
        players.at(current_player)->playTurn(tile);
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
    //creation of the architect
    Player* architect = new Architect("Architect",difficulty);
    players.push_back(architect);
    while (!(river->stay1() && pile->isEmpty())) {
       //turn of the architect
        if (current_player != 0) {
            cout << "Architect's turn!\n";
            cout << "Stones : " << players.at(current_player)->getStones() << "\n";
            Tile* chosen_tile_ptr = nullptr;
            int chosen_pos = -1;
            int pos = 0;

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
            if (!chosen_tile_ptr && !river->stay1()) {
                chosen_tile_ptr = &*river->begin();
                chosen_pos = 0;
            }

            // Vérifie que la tuile existe avant de l'utiliser
            if (chosen_tile_ptr) {
                cout << "Architect took the tile " << chosen_pos << "\n";
                players.at(1)->addStones(-chosen_pos);
                players.at(1)->playTurn(*chosen_tile_ptr);
            } else {
                cout << "Architect can't play.\n";
            }
            nextPlayer();
        }
        //turn of the player
        else {
            cout << "Your turn !"  << "\n";
            cout << *players.at(current_player) << "\n";
            int stones_before = players.at(0)->getStones();
            Tile& tile = pickRiver();
            int stones_after = players.at(0)->getStones();
            //player gives the stones he lost picking the tile to the architect
            players.at(1)->addStones(stones_after - stones_before);
            players.at(0)->playTurn(tile);
            nextPlayer();
        }
    }
}

void Game::endGame() {
    //displaying of each player's score thanks to method of Player
}