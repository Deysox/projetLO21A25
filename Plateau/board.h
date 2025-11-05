#ifndef PROJETLO21A25_PLATEAU_H
#define PROJETLO21A25_PLATEAU_H

#include <map>
#include <vector>
#include <string>
#include <unordered_map>

#include "../Utilitaires/position.h"
#include "../Utilitaires/rotation.h"
using namespace std;

// ===== A supprimer après =====
namespace Marilou {
    enum class Color{};
    class Cell;
}
// =====

namespace Barnabe {
    using namespace Marilou;

    class Board {
        unordered_map<Position, Cell*, PositionHasher> cells;
        unordered_map<Position, unsigned int, PositionHasher> heightmap;
        Position corner_tl;
        Position corner_br;
    public:
        // class neighbour_const_iterator {
        //     const Cell* current;
        //     neighbour_const_iterator(const Cell* c);
        // public:
        //     neighbour_const_iterator& operator++();
        //     const Cell& operator*();
        //     bool operator != (neighbour_const_iterator&);
        // };

        Board();
        ~Board();
        Board(const Board&);

        Board& operator=(const Board&);

        Cell* getCell(Position pos) const;
        Cell* getCell(int x, int y) const;

        unsigned int getHeight(Position pos) const;
        unsigned int getHeight(int x, int y) const;

        Position findCell(const Cell&) const;

        void setCell(Position pos, unsigned int h, const Cell& c);
        void setCell(int x, int y, unsigned int h, const Cell& c);

        void validPos(const vector<Position>&) const;

        friend ostream& operator<<(ostream& f, const Board& p);
    };
}

ostream& operator<<(ostream& f, const Barnabe::Board& p);

#endif //PROJETLO21A25_PLATEAU_H