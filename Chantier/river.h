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
        vector<Tile*> tiles;
        int max_tiles;
        Pile& pile;
        void fillriver();
    public:
        Tile& giveTile(size_t position);
        bool stay1()const;
        size_t getPosition(const Tile* t) const;
        River(size_t nb, Pile& pile);
        River(vector<Tile*>& tiles, size_t nb, Pile& pile): tiles(tiles), max_tiles(nb), pile(pile){};
        ~River();
        River(const River& r):tiles(r.tiles), max_tiles(r.max_tiles), pile(r.pile){};
        River& operator=(River& f);
    private:
        class RiverIterator {
            std::vector<Tile*>::iterator current;
            friend class River;
            RiverIterator(const std::vector<Tile*>::iterator& it)
                : current(it) {}
        public:
            // ++prefixe
            RiverIterator& operator++() {
                ++current;
                return *this;
            }

            RiverIterator& operator--() {
                --current;
                return *this;
            }

            bool operator!=(const RiverIterator& other) const {
                return current != other.current;
            }

            Tile& operator*() {
                return **current;
            }
        };

    public:
        RiverIterator begin() {
            return RiverIterator(tiles.begin());
        }

        RiverIterator end() {
            return RiverIterator(tiles.end());
        }
    };

    ostream& operator<<(ostream& f, Amalena::River& r);


}



#endif //PROJETLO21A25_RIVER_H