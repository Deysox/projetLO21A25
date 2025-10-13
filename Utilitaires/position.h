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
        Position(int x, int y) : posX(x), posY(y) {};

        int x() const {return posX;}
        int y() const {return posY;}

        Position operator+(const Position&);
        Position operator+(const Rotation&);
        Position operator-(const Position&);
        Position operator==(const Position&);
        Position operator!=(const Position&);

        bool adjacent(const Position&);
    };
}


#endif //PROJETLO21A25_POSITION_H