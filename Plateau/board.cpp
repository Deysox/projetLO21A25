#include "board.h"

namespace Barnabe {
    using namespace Marilou;

    Board::Board() : corner_br(0,0), corner_tl(0,0) {};
    Board::~Board() = default;
    Board::Board(const Board& b) {
        cells = b.cells;
        corner_tl = b.corner_tl;
        corner_br = b.corner_br;
    }

    Board &Board::operator=(const Board &b ) {
        if (&b != this) {
            cells = b.cells;
            corner_tl = b.corner_tl;
            corner_br = b.corner_br;
        }
        return *this;
    }

    const Cell* Board::getCell(Position pos) const {
        auto search = cells.find(pos);
        if (search != cells.end()) {
            return search->second.first;
        } else {
            return nullptr;
        }
    }

    const Cell *Board::getCell(int x, int y) const {
        return getCell(Position(x,y));
    }

    unsigned int Board::getHeight(Position pos) const {
        auto search = cells.find(pos);
        if (search != cells.end()) {
            return search->second.second;
        } else {
            return 0;
        }
    }

    unsigned int Board::getHeight(int x, int y) const {
        return getHeight(Position(x,y));
    }

    void Board::setCell(Position pos, unsigned int h, const Cell* c) {
        cells[pos] = pair<const Cell*, unsigned int>(c,h);
        if (pos.x() < corner_tl.x()) corner_tl = Position(pos.x(),corner_tl.y());
        else if (pos.x() > corner_br.x()) corner_br = Position(pos.x(),corner_br.y());

        if (pos.y() > corner_tl.y()) corner_tl = Position(corner_tl.x(),pos.y());
        else if (pos.y() < corner_br.y()) corner_br = Position(corner_br.x(),pos.y());
    }

    void Board::setCell(int x, int y, unsigned int h, const Cell *c) {
        setCell(Position(x,y),h,c);
    }

    std::pair<Position, Position> Board::getCorners() const {
        return {corner_tl,corner_br};
    }

    ostream& operator<<(ostream& f, const Barnabe::Board& b) {
        string output;

        Barnabe::Position ctl = b.getCorners().first;
        Barnabe::Position cbr = b.getCorners().second;

        int xindex_end = cbr.x();
        int yindex_end = cbr.y()-1;

        for (int yindex = ctl.y(); yindex >= yindex_end; yindex--) {
            string line1;
            string line2;
            for (int xindex = ctl.x(); xindex <= xindex_end; xindex++) {
                if (xindex%2 == 0) {
                    const Marilou::Cell* cellToPlace = b.getCell(xindex,yindex);
                    unsigned int heightToPlace = b.getHeight(xindex,yindex);
                    line1 += (cellToPlace ? cellToPlace->displayTop(heightToPlace) : "    ");
                    line2 += (cellToPlace ? cellToPlace->displayBottom() : "    ");
                } else {

                    const Marilou::Cell* cellToPlace = b.getCell(xindex,yindex+1);
                    line1 += (cellToPlace ? cellToPlace->displayBottom() : "    ");

                    cellToPlace = b.getCell(xindex,yindex);
                    unsigned int heightToPlace = b.getHeight(xindex,yindex);

                    line2 += (cellToPlace ? cellToPlace->displayTop(heightToPlace) : "    ");
                }
            }
            f << line1 << endl << line2 << endl;
        }

        return f;


    }


}

