#include "tile.h"


namespace Barnabe {
    int Tile::id = 0;

    Tile::~Tile() {
        for (auto it = cells.begin(); it != cells.end(); it++) {
            delete *it; // Désallocation des cases
        }
    }


    StartingTile::StartingTile() {
        cells.push_back(new Cell(id, Color::BLUE, Type::PLACE));
        cells.push_back(new Cell(id, Color::GREY, Type::QUARRY));
        cells.push_back(new Cell(id, Color::GREY, Type::QUARRY));
        cells.push_back(new Cell(id, Color::GREY, Type::QUARRY));
    }

    std::vector<Position> StartingTile::calculatePositions(const Position& p, const Rotation& r) const {
        return {p,
            p+(Rotation(0)+r),
            p+(Rotation(2)+r),
            p+(Rotation(4)+r)};
    }

    ClassicTile::ClassicTile(Color c1, Type t1, Color c2, Type t2, Color c3, Type t3) {
        cells.push_back(new Cell(id,c1,t1));
        cells.push_back(new Cell(id,c2,t2));
        cells.push_back(new Cell(id,c3,t3));
    }

    std::vector<Position> ClassicTile::calculatePositions(const Position& p, const Rotation& r) const {
        return {p,
            p+(Rotation(0)+r),
            p+(Rotation(1)+r)};
    }

    ostream& operator<<(ostream& f, ClassicTile& c) {
        f << c.getCell(1)->displayTop(1) << endl;
        f << c.getCell(1)->displayBottom() << c.getCell(2)->displayTop(1) << endl;
        f << c.getCell(0)->displayTop(1) << c.getCell(2)->displayBottom() << endl;
        f << c.getCell(0)->displayBottom() << endl;
        return f;

    }


    AthenaTile::AthenaTile(Color c1, Color c2, Type t) {
        cell = new BicolorCell(id,c1,t,c2,0);
        cells.push_back(cell);
    }

    std::vector<Position> AthenaTile::calculatePositions(const Position& p, const Rotation& r) const {
        cell->setRotation(r);
        return {p};
    }


    //to be modified (Qt adaptation)
    string Tile::typeToString(Type t) {
        switch(t) {
            case Type::PLACE: return "PLACE";
            case Type::DISTRICT: return "DISTRIC";
            case Type::QUARRY: return "QUARRY";
            default: return "UNKNOWN";
        }
    }

    //to be modified (Qt adaptation)
    string Tile::toString() {
        std::ostringstream oss;
        for (size_t i = 0; i < cells.size(); ++i) {
            oss << "Cell " << (i + 1) << ": "
                << typeToString(cells[i]->getType())
                << " | ";
        }
        return oss.str();
    }



}
