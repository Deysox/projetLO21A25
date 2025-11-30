#include "tile.h"


namespace Barnabe {
    int Tile::id = 0;

    Tile::~Tile() {
        for (auto it = cells->begin(); it != cells->end(); it++) {
            delete *it; // Désallocation des cases
        }
        delete cells; // Désallocation du vecteur
    }


    StartingTile::StartingTile() {
        cells->push_back(new Cell(id, Color::BLUE, Type::PLACE));
        cells->push_back(new Cell(id, Color::GREY, Type::QUARRY));
        cells->push_back(new Cell(id, Color::GREY, Type::QUARRY));
        cells->push_back(new Cell(id, Color::GREY, Type::QUARRY));
    }

    std::vector<Position> StartingTile::calculatePositions(Position p, Rotation r) const {
        return {p,
            p+(Rotation(0)+r),
            p+(Rotation(2)+r),
            p+(Rotation(4)+r)};
    }

    ClassicTile::ClassicTile(Color c1, Type t1, Color c2, Type t2, Color c3, Type t3) {
        cells->push_back(new Cell(id,c1,t1));
        cells->push_back(new Cell(id,c2,t2));
        cells->push_back(new Cell(id,c3,t3));
    }

    std::vector<Position> ClassicTile::calculatePositions(Position p, Rotation r) const {
        return {p,
            p+(Rotation(0)+r),
            p+(Rotation(1)+r)};
    }

    ostream& operator<<(ostream& f, ClassicTile& c) {
        vector<const Cell*> cells_vector = *(c.cells);
        f << cells_vector[0]->displayTop(1) << endl;
        f << cells_vector[0]->displayBottom() << cells_vector[1]->displayTop(1) << endl;
        f << cells_vector[2]->displayTop(1) << cells_vector[1]->displayBottom() << endl;
        f << cells_vector[2]->displayBottom() << endl;
        return f;

    }


    AthenaTile::AthenaTile(Color c1, Color c2, Type t) {
        cell = new BicolorCell(id,c1,t,c2,0);
        cells->push_back(cell);
    }

    std::vector<Position> AthenaTile::calculatePositions(Position p, Rotation r) const {
        cell->setRotation(r);
        return {p};
    }






}
