//
// Created by barnab on 13/10/2025.
//

#ifndef PROJETLO21A25_POSITION_H
#define PROJETLO21A25_POSITION_H
#include "rotation.h"

namespace Barnabe {
    class Position {
        int posX;
        int posY;
    public:
        Position(int x = 0, int y = 0) : posX(x), posY(y) {};

        int x() const {return posX;}
        int y() const {return posY;}

        Position operator+(const Position& p) const {return Position(posX + p.posX, posY+p.posY);}
        Position operator+(const Rotation&) const;
        Position operator-(const Position& p) const {return Position(posX - p.posX, posY - p.posY);}
        bool operator==(const Position& p) const {return (posX == p.posX) and (posY == p.posY);}
        bool operator!=(const Position& p) const {return !((posX == p.posX) and (posY == p.posY));}

        bool estAdjacent(const Position&) const;

        class neighbor_iterator {
            int rot;
            int x;
            int y;
            neighbor_iterator(int px, int py, int r) : x(px),y(py),rot(r) {}
            friend class Position;
        public:
            neighbor_iterator& operator++() {
                rot++;
                return *this;
            }
            neighbor_iterator operator++(int) {
                int old = rot;
                rot++;
                return neighbor_iterator(x,y,old);
            }
            Position operator*(){return Position(x,y) + Rotation(rot);}
            bool operator!=(const neighbor_iterator& c){return rot == c.rot;};
            bool operator==(const neighbor_iterator& c) {return rot != c.rot;}
        };

        neighbor_iterator begin() const {return neighbor_iterator(posX,posY, 0);}
        neighbor_iterator end() const {return neighbor_iterator(posX,posY, 6);}
    };

    struct PositionHasher {
        std::size_t operator()(const Position& p) const {
            return std::hash<int>()(p.x()) ^ (std::hash<int>()(p.y()) << 1);
        }
    };
}


#endif //PROJETLO21A25_POSITION_H