#include "board.h"

namespace Barnabe {
    using namespace Marilou;

    Board::Board() : corner_br(0,0), corner_tl(0,0) {};
    Board::~Board() = default;
    Board::Board(const Board& b) {
        cells = b.cells;
        heightmap = b.heightmap;
        corner_tl = b.corner_tl;
        corner_br = b.corner_br;
    }

    Board &Board::operator=(const Board &b ) {
        if (&b != this) {
            cells = b.cells;
            heightmap = b.heightmap;
            corner_tl = b.corner_tl;
            corner_br = b.corner_br;
        }
        return *this;
    }

    const Cell* Board::getCell(Position pos) const {
        auto search = cells.find(pos);
        if (search != cells.end()) {
            return search->second;
        } else {
            return nullptr;
        }
    }

    const Cell *Board::getCell(int x, int y) const {
        return getCell(Position(x,y));
    }

    unsigned int Board::getHeight(Position pos) const {
        auto search = heightmap.find(pos);
        if (search != heightmap.end()) {
            return search->second;
        } else {
            return 0;
        }
    }

    unsigned int Board::getHeight(int x, int y) const {
        return getHeight(Position(x,y));
    }

    void Board::setCell(Position pos, unsigned int h, const Cell* c) {
        cells[pos] = c;
        heightmap[pos] = h;
    }

    void Board::setCell(int x, int y, unsigned int h, const Cell *c) {
        setCell(Position(x,y),h,c);
    }

    void Board::validPos(const vector<Position> &) const {
        // Nécessite le pointeur vers la tuile des cases.
        return;
    }

}

ostream& operator<<(ostream& f, const Barnabe::Board& p) {
    // Nécessite l'affichage de cell
}