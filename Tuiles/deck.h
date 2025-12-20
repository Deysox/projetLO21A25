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

    /**
     * Classe pour gérer la création des tuiles à partir du fichier json
     */
    class Deck {
    public:
        /**
         * Map pour convertir les types string en Color
         */
        static map<string, Color> stringToColor;
        /**
         * Map pour convertir les types string en Type
         */
        static map<string, Type> stringToType;
    private :
        /**
         * Vecteur avec toutes les tuiles nécessaires à la partie
         */
        vector <Barnabe::ClassicTile*> tiles;
    public:
        /**
         * Constructeur
         * @param nb_players_game le nombre de joueurs dont dépend le nombre de tuiles
         */
        Deck(int nb_players_game);

        /**
         * Destructeur qui libère les tuiles
         */
        ~Deck();

        /**
         * Getter pour les tuiles
         * @return un vecteur de tuiles
         */
        const vector<Barnabe::ClassicTile*>& getTiles() const{return tiles;}

        /**
         * Surcharge opérateur d'affectation
         * @param f référence sur le deck
         * @return le deck courant
         */
        Deck& operator=(const Deck& f) {
            if (this!=&f) this->tiles = f.tiles;
            return *this;
        }
    };
}


#endif //PROJETLO21A25_JEU_H