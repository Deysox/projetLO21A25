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

    class Deck {
    public:
        /*
         *map that allows a conversion of types : string - Color
         */
        static map<string, Color> stringToColor;
        /*
         *map that allows a conversion of types : string - Type
         */
        static map<string, Type> stringToType;
    private :
        /*
         *attribut tiles is a vector of ClassicTiles that we fill w/ the json file
         */
        vector <Barnabe::ClassicTile*> tiles;
    public:
        /*
         *constructor
         *@param nb_player_game : so that we can adapt the tiles in the deck
         */
        Deck(int nb_players_game);
        /*
         *destructor that frees the tiles
         */
        ~Deck();
        /*
         *getter for tiles
         */
        const vector<Barnabe::ClassicTile*>& getTiles() const{return tiles;}
        /*
         *operator =
         */
        Deck& operator=(const Deck& f) {
            if (this!=&f) this->tiles = f.tiles;
            return *this;
        }
    };
}

#endif //PROJETLO21A25_JEU_H