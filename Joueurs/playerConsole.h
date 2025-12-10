//
// Created by elobo on 10/12/2025.
//

#ifndef PROJETLO21A25_PLAYERCONSOLE_H
#define PROJETLO21A25_PLAYERCONSOLE_H
#include "Player.h"

namespace Barnabe {
    class PlayerConsole : public Player {
    public:
        PlayerConsole(const string& s) : Player(s){}
        void displayBoard() override;
        void placeTile(const Tile &tile) override;
    };
    //solo variant
    class ArchitectConsole : public PlayerConsole {
        int difficulty;
        vector <Tile*> architect_tiles;
    public:
        ArchitectConsole(const std::string& name, int d)
            : PlayerConsole(name), difficulty(d) {}
        void playTurn(const Tile& t) override {
            architect_tiles.push_back(const_cast<Tile*>(&t));
        }
    };
}
#endif //PROJETLO21A25_PLAYERCONSOLE_H