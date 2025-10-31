#include "game.h"
#include <iostream>
#include <vector>

Partie* Partie::instance = nullptr;

Partie::Partie() {
    std::cout << "Constructeur de la partie." << std::endl;
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

