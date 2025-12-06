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

namespace Eloise {
    using namespace std;
    using json = nlohmann::json;
    using namespace Barnabe;

    //deck handles lifecycle of tiles
    class Deck {
    public:
        static map<string, Color> stringToColor;
        static map<string, Type> stringToType;
    private :
        //tiles from json
        vector <Barnabe::ClassicTile*> tiles;
    public:
        //constructor which constructs the tiles from json file
        Deck(int nb_players_game);
        //Deck frees the tiles
        ~Deck();
        //const vector<Barnabe::ClassicTile*>& getTiles() const{return tiles;}
    };
}


#endif //PROJETLO21A25_JEU_H