//
// Created by elobo on 10/12/2025.
//

#ifndef PROJETLO21A25_PLAYERCONSOLE_H
#define PROJETLO21A25_PLAYERCONSOLE_H
#include "player.h"
using namespace Barnabe;
namespace Eloise {
    class PlayerConsole : public Player {
    public:
        /*
         *constructor
         *@param name of player
         */
        PlayerConsole(const string& s) : Player(s){}
        /*
         *method that uses << operator to display board
         */
        void displayBoard() override;
        /*
         *method that allows player to choose a position and a rotation
         *then calls place() method to actually place tile
         *then updates the amount of stones
         *@param reference of chosen tile
         */
        void placeTile(const Tile &tile) override;
    };
    /*
     *class used for solo variant
     */
    class ArchitectConsole : public PlayerConsole {
        /*
         *attribut difficulty for score
         */
        int difficulty;
        /*
         *attribut which is simply a vector of tiles because architect doesn't have to place his tile
         */
        vector <Tile*> architect_tiles;
    public:
        /*
         *constructor of architect
         *uses PlayerConsole constructor
         *@param name : name of player
         *@param d : difficulty
         */
        ArchitectConsole(const std::string& name, int d)
            : PlayerConsole(name), difficulty(d) {}
        /*
         *override of playTurn()
         *during his turn architect has only to add tiles to his vector
         */
        void playTurn(const Tile& t) override {
            architect_tiles.push_back(const_cast<Tile*>(&t));
        }
    };
}
#endif //PROJETLO21A25_PLAYERCONSOLE_H