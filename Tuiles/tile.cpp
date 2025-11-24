#include "tile.h"


namespace Barnabe {
    Tile::~Tile() {
        for (auto it = cells->begin(); it != cells->end(); it++) {
            delete *it;
        }
        delete cells;
    }


    StartingTile::StartingTile() {
        cells->push_back(new Cell(this, Color::BLUE, Type::PLACE));
        cells->push_back(new Cell(this, Color::GREY, Type::QUARRY));
        cells->push_back(new Cell(this, Color::GREY, Type::QUARRY));
        cells->push_back(new Cell(this, Color::GREY, Type::QUARRY));
    }

    std::vector<Position> StartingTile::calculatePositions(Position p, Rotation r) const {
        return {p,
            p+(Rotation(0)+r),
            p+(Rotation(2)+r),
            p+(Rotation(4)+r)};
    }

    ClassicTile::ClassicTile(Color c1, Type t1, Color c2, Type t2, Color c3, Type t3) {
        cells->push_back(new Cell(this,c1,t1));
        cells->push_back(new Cell(this,c2,t2));
        cells->push_back(new Cell(this,c3,t3));
    }

    std::vector<Position> ClassicTile::calculatePositions(Position p, Rotation r) const {
        return {p,
            p+(Rotation(0)+r),
            p+(Rotation(1)+r)};
    }

    AthenaTile::AthenaTile(Color c1, Color c2, Type t) {
        cell = new BicolorCell(this,c1,t,c2,0);
        cells->push_back(cell);
    }

    std::vector<Position> AthenaTile::calculatePositions(Position p, Rotation r) const {
        cell->setRotation(r);
        return {p};
    }






}
