//
// Created by barnab on 05/10/2025.
//

#ifndef PROJETLO21A25_RIVER_H
#define PROJETLO21A25_RIVER_H
#include <vector>
#include <iostream>
#include "tile.h"
#include "game.h"
#include "pile.h"
using namespace std;
using namespace Marilou;


namespace Amalena {
    class River{
        vector<Tile*> tiles;
        int max_tiles;
        Pile& pile;

        River(const River& f)=delete;
        River& operator=(River& f)=delete;
        void fillriver();
    public:
        Tile& giveTile(size_t position);
        bool stay1()const;
        size_t getPosition(const Tile* t) const;
        River( size_t nb, Pile& pile);
        River(const vector<Tile*> tiles, size_t nb, Pile& pile): tiles(tiles), max_tiles(nb), pile(pile){};
        ~River();;
    };
}
ostream& operator<<(ostream& f, const Amalena::River& r);
#endif //PROJETLO21A25_RIVER_H