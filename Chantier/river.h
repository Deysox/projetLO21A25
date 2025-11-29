#ifndef PROJETLO21A25_RIVER_H
#define PROJETLO21A25_RIVER_H
#include <vector>
#include <iostream>
#include "tile.h"
#include "pile.h"
using namespace std;
using namespace Barnabe;


namespace Amalena {
    class River{
        vector<ClassicTile*> tiles;
        int max_tiles;
        Pile& pile;

        River(const River& r):tiles(r.tiles), max_tiles(r.max_tiles), pile(r.pile){};
        River& operator=(River& f)=delete;
        void fillriver();
    public:
        ClassicTile& giveTile(size_t position);
        bool stay1()const;
        size_t getPosition(const ClassicTile* t) const;
        River(size_t nb, Pile& pile);
        River(vector<ClassicTile*>& tiles, size_t nb, Pile& pile): tiles(tiles), max_tiles(nb), pile(pile){};
        ~River();
    };
}
ostream& operator<<(ostream& f, const Amalena::River& r);
#endif //PROJETLO21A25_RIVER_H