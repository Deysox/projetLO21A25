#include "game.h"
#include "river.h"
#include <iostream>
#include <vector>

Game* Game::instance = nullptr;

static size_t nb_players_max = 4;

Game::Game(size_t tile_count, string variant, string mode, string difficulty, size_t nb_players) :
//how to choose and fill vector of tiles for the pile ?
//pile(new Amalena::Pile()),
deck(new Deck()),
river(new Amalena::River()),
tile_count(tile_count),
variant(variant),
mode(mode),
difficulty(difficulty),
nb_players(nb_players),
players(nb_players,nullptr) {
    for (int i = 0; i < nb_players; i++) {
        cout << "Name ?";
        string name;
        cin >> name;
        addPlayer(name);
    }
}

void Game::displayPlayers() {
    for (Barnabe::Player* player : players) {
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
        Barnabe::Player* p = new Barnabe::Player(name);
        players.push_back(p);
        nb_players++;
    }
}

Barnabe::Player* Game::getPlayer(size_t position) {
    if (position < nb_players) {
        return players.at(position);
    }
    else {
        //Put an exception instead
        cout << "Invalid position.";
    }
}

void Game::informationsGame() {
    cout << "Game informations : \n";
    cout << "Tile count : " << tile_count << "\n";
    cout << "Mode : " << mode << "\n";
    cout << "Difficulty : " << difficulty << "\n";
    cout << "Number of players max : " << nb_players_max << "\n";
    cout << "Number of players : " << nb_players << "\n";
    for (int i =  0; i < nb_players; i++) {
        displayPlayers();
    }
}

void Game::nextPlayer() {
    current_player++;
    current_player %= nb_players;
}

void Game::nextArchitect() {
    architect++;
    architect %= nb_players;
}

/* River :
1 player : 4 tiles
2 players : 4 tiles
3 players : 5 tiles
4 players : 6 tiles
*/

void Game::fillRiver() {
    //pick in the pile to file the river
}

void Game::pickRiver() {
    //player clicks on a tile to acknowledge the cost of the tile using getPosition()
    //player picks a tile in the river using river.giveTile()
    //getStones() to acknowledge if he can buy the tile
    //setStones() to modify the amont of stones he's got left
}

//must be a loop : until  river.stay1() AND pile.isEmpty()
void Game::manageGame() {
    cout << "Start of the game ! \n";
    cout << "Architect : " << players.at(architect)->getName() << "\n";
    cout << "Current player : " << players.at(current_player)->getName() << "\n";
    //display board of current player
    //display river
    //player picks a tile in river (pickRiver())
    //player adds his tile to board
    //next player (nextPlayer())
    //if stay1 in river :
        //fill River (fillRiver())
        //next architect (nextArchitect())
}




