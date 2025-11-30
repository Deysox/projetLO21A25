//
// Created by elobo on 20/11/2025.
//

#include "game.h"
#include "river.h"
#include <iostream>
#include <vector>

//static attributs
Game* Game::instance = nullptr;
size_t Game::nb_players_max = 4;

Game::Game(size_t tile_count, string variant, string mode, string difficulty, size_t nb_players) :
tile_count(tile_count),
variant(variant),
mode(mode),
difficulty(difficulty),
nb_players(nb_players),
deck(new Deck(nb_players)),
pile(new Amalena::Pile(*deck)),
river(new Amalena::River(nb_players+2,*pile))
{
    //reserve much better that init w/ nullptr because of push_back that would add after the nullptrs
    players.reserve(nb_players);
    for (size_t i = 0; i < nb_players; i++) {
        cout << "Name ?";
        string name;
        cin >> name;
        addPlayer(name);
    }
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
        Barnabe::Player* p = new Barnabe::Player(name);
        players.push_back(p);
        nb_players++;
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

ClassicTile& Game::pickRiver() {
    //diplaying of river and the position of the tiles
    cout << "River : " << river;
    //player says that he wants a tile at a certain position
    cout << "\n";
    cout << "Write the position of the tile you want : ";
    int position = 0;
    cin >> position;
    //getStones() to acknowledge if he can buy the tile ==> loop while player.getStones() < position
    while (players[current_player]->getStones() < position) {
        cout << "You don't have enough stones, select another position : ";
        cin >> position;
    }
    //player actually picks the tile in the river using river.giveTile()
    Barnabe::ClassicTile& chosen_tile = river->giveTile(position);
    //setStones() to modify the amont of stones he's got left
    players[current_player]->setStones(players[current_player]->getStones() - position);
    return chosen_tile;
}

void Game::manageGame() {
    cout << "Start of the game ! \n";
    while (!(river->stay1() && pile->isEmpty())) {
        cout << "Current player : " << players.at(current_player);
        Barnabe::ClassicTile& tile = pickRiver();
        players.at(current_player)->playTurn(tile);
        nextPlayer();
    }
}

void Game::endGame() {
    //displaying of each player's score thanks to method of Player
}