#include "game.h"
#include "river.h"
#include <iostream>
#include <vector>

Partie* Partie::instance = nullptr;

Partie::Partie(size_t tile_count, string variant, string mode, string difficulty, size_t nb_players) : tile_count(tile_count), variant(variant), mode(mode), difficulty(difficulty), nb_players(nb_players) {
    //penser à allouer l'espace pour la rivière
}

void Partie::displayPlayers() {
    for (Barnabe::Player* player : players) {
        cout << player->getName() << "\n";
    }
}

void Partie::addPlayer(const string& name) {
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

Barnabe::Player* Partie::getPlayer(size_t position) {
    if (position < nb_players) {
        return players.at(position);
    }
    else {
        //Put an exception instead
        cout << "Invalid position.";
    }
}

void Partie::informationsPartie() {
    std::cout << "Informations de la partie." << std::endl;
}

