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

        Position operator+(const Position&) const;
        Position operator+(const Rotation&) const;
        Position operator-(const Position&) const;
        bool operator==(const Position&) const;
        bool operator!=(const Position&) const;

        bool estAdjacent(const Position&) const;

        class neighbor_iterator {
            int rot;
            int x;
            int y;
            neighbor_iterator(int px, int py, int rot);
        public:
            neighbor_iterator& operator++();
            neighbor_iterator operator++(int);
            Position operator*();
            bool operator!=(const neighbor_iterator&);
            bool operator==(const neighbor_iterator&);
        };

        neighbor_iterator begin() const;
        neighbor_iterator end() const;
    };

    struct PositionHasher {
        std::size_t operator()(const Position& p) const {
            return std::hash<int>()(p.x()) ^ (std::hash<int>()(p.y()) << 1);
        }
    };
}


#endif //PROJETLO21A25_POSITION_H