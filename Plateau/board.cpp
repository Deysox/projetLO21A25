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

    Cell *Board::getCell(Position pos) const {
        auto search = cells.find(pos);
        if (search != cells.end()) {
            return search->second;
        } else {
            return nullptr;
        }
    }

    Cell *Board::getCell(int x, int y) const {
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












}