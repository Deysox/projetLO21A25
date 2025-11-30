#include "deck.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include "cell.h"

using namespace std;
using json = nlohmann::json;
/*using Tile = Barnabe::Tile;
using Cell = Barnabe::Cell;
using ClassicTile = Barnabe::ClassicTile;*/
using namespace Marilou;

Deck::Deck(int nb_players_game) {
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
        //reservation of space for tiles' vector
        tiles.reserve(data.size());
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
            array <Cell*, 3> game_cells;
            for (auto& c : game_cells) {
                c = nullptr;
            }
            ClassicTile* game_tile = new ClassicTile(game_cells);
            //creation of cells that belong to the tile
            Cell* cell1 = new Cell(game_tile, Marilou::stringToColor[color1], Marilou::stringToType[type1]);
            game_cells[0] = cell1;
            Cell* cell2 = new Cell(game_tile, Marilou::stringToColor[color2], Marilou::stringToType[type2]);
            game_cells[1] = cell2;
            Cell* cell3 = new Cell(game_tile, Marilou::stringToColor[color3], Marilou::stringToType[type3]);
            game_cells[2] = cell3;
            //add tile to the deck
            tiles.push_back(game_tile);
        }
    } else {
        cout << "Error w/ file." << endl;
    }
}

Deck::~Deck() {
    for (auto& t : tiles) {
        delete t;
    }
}
