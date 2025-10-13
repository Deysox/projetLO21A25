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

        Position operator+(const Position&);
        Position operator+(const Rotation&);
        Position operator-(const Position&);
        Position operator==(const Position&);
        Position operator!=(const Position&);

        bool estAdjacent(const Position&) const;

        class neighbor_iterator {
            int rot;
            neighbor_iterator() : rot(0) {}
        public:
            neighbor_iterator& operator++();
            neighbor_iterator& operator++(int);
            Position operator*();
            bool operator!=(const neighbor_iterator&);
            bool operator==(const neighbor_iterator&);
        };

        const neighbor_iterator begin() const;
        const neighbor_iterator end() const;
    };
}


#endif //PROJETLO21A25_POSITION_H