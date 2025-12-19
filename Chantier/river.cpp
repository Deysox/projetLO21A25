//
// Created by elobo on 02/12/2025.
//


#include "river.h"
#include "pile.h"

using namespace Barnabe;
namespace Amalena {
    River::River(size_t nb, Pile& pile):max_tiles(nb), pile(pile)
    {
        River::fillriver();
    }
    River& River::operator=(const River& f) {
        if (this!=&f) {
            this->tiles = f.tiles;
            this->max_tiles = f.max_tiles;
            this->pile = f.pile;
        }
        return *this;
    }
    void River::fillriver()
    {
        while (tiles.size()<max_tiles) tiles.push_back(pile.Draw());
    }

    Barnabe::Tile& River::giveTile(size_t position)
    {
        if (position>tiles.size()) throw std::out_of_range("position out of range dans la rivière");
        Tile* t=tiles[position-1];
        tiles.erase(tiles.begin()+(position-1));
        if (stay1()) fillriver();
        return *t;

    }

    bool River::stay1() const
    {
        return tiles.size()==1;
    }

    size_t River::getPosition(const Tile* t) const
    {
        size_t position=0;// n'existe pas
        for (auto it= tiles.begin() ;it!=tiles.end(); ++it)
        {   ++position;
            if (*it==t) return position;
        }
        return 0;

    }
    River::~River()
    {}

    string River::toString() const {
        std::ostringstream oss;
        for (size_t i = 0; i < tiles.size(); ++i) {
            oss << "Tile " << (i + 1) << ": " << tiles[i]->toString() << "\n";
        }
        return oss.str();
    }

    ostream& operator<<(std::ostream& f, Amalena::River& river) {
        f << "River:\n";
        int pos = 1;
        for (auto it = river.begin(); it != river.end(); ++it) {
            Tile& tile = *it;
            if (ClassicTile* ct = dynamic_cast<ClassicTile*>(&tile)) {
                f << "Tile " << pos++ << " :\n" << *ct << "\n";
            } else {
                f << "Can't display Tile " << pos++ << "\n";
            }
        }
        return f;
    }
}