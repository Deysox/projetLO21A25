#include "deck.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

using namespace std;
using json = nlohmann::json;

Deck::Deck() {
    ifstream fichier("tiles.json");
    if (fichier.is_open()){
        json data;
        fichier >> data;
        fichier.close();
        int id = 0;
        string nb_players = " ";
        int nb_players_int = 0;
        string type1 = " ";
        string color1 = " ";
        string type2 = " ";
        string color2 = " ";
        string type3 = " ";
        string color3 = " ";
        for (const auto& tile : data) {
            id = tile["id"];
            nb_players = tile["Nb Players"];
            nb_players_int = stoi(nb_players);
            type1 = tile["Type 1"];
            type2 = tile["Type 2"];
            type3 = tile["Type 3"];
            color1 = tile["Color 1"];
            color2 = tile["Color 2"];
            color3 = tile["Color 3"];
            //creation of tile
            Marilou::Tile* game_tile = new Marilou::Tile();
            //creation of cells that belong to the tile
            Marilou::Cell* cell1 = new Marilou::Cell(game_tile, Marilou::stringToColor[color1], Marilou::stringToType[type1]);
            Marilou::Cell* cell2 = new Marilou::Cell(game_tile, Marilou::stringToColor[color2], Marilou::stringToType[type2]);
            Marilou::Cell* cell3 = new Marilou::Cell(game_tile, Marilou::stringToColor[color3], Marilou::stringToType[type3]);
            //add tile to the deck
            tiles.push_back(game_tile);
        }
    } else {
        cout << "Error w/ file." << endl;
    }
}