//
// Created by barnab on 05/10/2025.
//

#ifndef PROJETLO21A25_JEU_H
#define PROJETLO21A25_JEU_H

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include "tile.h"
#include "cell.h"

using namespace std;
using json = nlohmann::json;
using Tile = Barnabe::Tile;

//deck handles lifecycle of tiles
class Deck {
private :
    //tiles from json
    vector <Tile*> tiles;
public:
    //constructor which constructs the tiles from json file
    Deck(int nb_players_game);
    //Deck frees the tiles
    ~Deck();
    const vector<Tile*>& getTiles() const{return tiles;}
};

#endif //PROJETLO21A25_JEU_H