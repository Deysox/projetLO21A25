#include "game.h"
#include <iostream>

Partie* Partie::instance = nullptr;

Partie::Partie() {
    std::cout << "Constructeur de la partie." << std::endl;
}

void Partie::informationsPartie() {
    std::cout << "Informations de la partie." << std::endl;
}

