#include "tile.h"


namespace Barnabe {
    int Tile::id = 0;

    Tile::~Tile() {
        for (auto it = begin(); it != end(); it++) {
            delete it->second.first; // Désallocation des cases
        }
    }

    const Cell* Tile::getCell(Position pos) {
        return Board::getCell(pos);
    }

    void Tile::setCell(const Cell* c, Position pos) {
        Board::setCell(pos,1,c);
    }

    void Tile::rotate() {
        rotationHook();

        unordered_map<Position, pair<const Cell*, unsigned int>, PositionHasher> final;
        for (auto it = begin(); it != end(); it ++) {
            int q = it->first.x();
            int r = it->first.y();
            int s = -q-r;

            int q_final = -r;
            int r_final = -s;
            final[Position(q_final,r_final)] = cells[it->first];
        }
        cells = final;
    }

    void Tile::rotate(Rotation r) {
        for (int i = 0; i < r.value(); i++) rotate();
    }

    void Tile::placeIn(Board* b, Position offset, Rotation r) {
        rotate(r);
        for (auto it = begin(); it != end(); it ++) {
            Position pos = it->first;
            unsigned int hght = it->second.second;
            const Cell* cell = it->second.first;

            b->setCell(pos+offset, getHeight(pos+offset)+hght, cell);
        }
    }


    StartingTile::StartingTile() {
        setCell(new Cell(id, Color::BLUE, Type::PLACE),Position(0,0));
        setCell(new Cell(id, Color::GREY, Type::QUARRY),Position(0,0)+Rotation(0));
        setCell(new Cell(id, Color::GREY, Type::QUARRY),Position(0,0)+Rotation(2));
        setCell(new Cell(id, Color::GREY, Type::QUARRY),Position(0,0)+Rotation(4));
    }

    void StartingTile::rotationHook() {
        return;
    }


    ClassicTile::ClassicTile(Color c1, Type t1, Color c2, Type t2, Color c3, Type t3) {
        setCell(new Cell(id,c1,t1),Position(0,0));
        setCell(new Cell(id,c2,t2),Position(0,0)+Rotation(0));
        setCell(new Cell(id,c3,t3),Position(0,0)+Rotation(1));
    }

    void ClassicTile::rotationHook() {
        return;
    }


    AthenaTile::AthenaTile(Color c1, Color c2, Type t) {
        cell = new BicolorCell(id,c1,t,c2,0);
        setCell(cell,Position(0,0));
    }

    void AthenaTile::rotationHook() {
        Rotation r= cell->getRotation();
        cell->setRotation(r++);
    }









}
