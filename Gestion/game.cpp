#include "game.h"
#include "river.h"
#include <iostream>
#include <vector>

Game* Game::instance = nullptr;

Game::Game(size_t tile_count, string variant, string mode, string difficulty, size_t nb_players) : tile_count(tile_count), variant(variant), mode(mode), difficulty(difficulty), nb_players(nb_players) {
    //penser � allouer l'espace pour la rivi�re
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
    std::cout << "Informations Game." << std::endl;
}

void Game::nextPlayer() {
    current_player++;
    current_player %= nb_players;
}

void Game::nextArchitect() {
    architect++;
    architect %= nb_players;
}
