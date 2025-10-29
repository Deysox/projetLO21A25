#ifndef PROJETLO21A25_JOUEUR_H
#define PROJETLO21A25_JOUEUR_H

#include "board.h"
#include "boardmanager.h"
#include <string>

namespace Barnabe {
    class Player {
        string name;
        BoardManager board;
        int stones;
    public:
        Player(const string& s);
        ~Player();

        const string& getName() const;

        int getStones() const;
        void setStones(int n);
        void addStones(int n);

        bool placeTile(const Tile&, Position, Rotation);

        int score() const;

    };
}


#endif //PROJETLO21A25_JOUEUR_H