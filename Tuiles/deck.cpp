#include "deck.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include "cell.h"

namespace Eloise {
    using namespace std;
    using json = nlohmann::json;
    using namespace Barnabe;

    // Tables de conversion des string vers les enumérations
    map<string, Color> Deck::stringToColor = {{"Blue",Color::BLUE},{"Red",Color::RED},{"Green",Color::GREEN},{"Yellow",Color::YELLOW},{"Grey",Color::GREY},{"Purple",Color::PURPLE}};
    map<string, Type> Deck::stringToType = {{"District", Type::DISTRICT},{"Place", Type::PLACE},{"Quarry", Type::QUARRY}};

    Deck::Deck(int nb_players_game) {
        ifstream fichier("tiles_2.json"); // Lecture du fichier
        if (fichier.is_open()){
            json data = json::parse(fichier); // Parsing des données
            fichier.close();
            for (const auto& tile : data) {

                if (tile["players"] <= nb_players_game) { // Vérification du nombre de joueurs dans la partie
                    string t1 = tile["cells"][0]["type"];
                    string t2 = tile["cells"][1]["type"];
                    string t3 = tile["cells"][2]["type"];
                    string c1 = tile["cells"][0]["color"];
                    string c2 = tile["cells"][1]["color"];
                    string c3 = tile["cells"][2]["color"];


                    ClassicTile* game_tile = new ClassicTile( // Instanciation de la tuile
                        stringToColor[c1],stringToType[t1],
                        stringToColor[c2],stringToType[t2],
                        stringToColor[c3],stringToType[t3]
                    );
                    tiles.push_back(game_tile);  // Ajout dans le plateau
                }
            }
        } else {
            throw FileException("Impossible d'ouvrir le fichier des tuiles.");
        }
    }

    Deck::~Deck() {
        for (auto& t : tiles) {
            delete t;
        }
    }
}


