//
// Created by barnab on 05/11/2025.
//
#include "position.h"

namespace Barnabe {
    Position Position::operator+(const Rotation& r) const {
        Position output;
        switch (r.value()) {
            case 0:
                output = Position(posX,posY+1);
                break;
            case 1:
                output = Position(posX+1,posY+1);
                break;
            case 2:
                output = Position(posX+1,posY-1);
                break;
            case 3:
                output = Position(posX,posY-1);
                break;
            case 4:
                output = Position(posX-1,posY-1);
                break;
            case 5:
                output = Position(posX-1,posY+1);
                break;
            default:
                output = Position(posX,posY);
                break;
        }

        return output;
    }

    bool Position::estAdjacent(const Position& p) const {
        for (auto it = begin(); it != end(); ++it) {
            if (*it == p) return true;
        }
        return false;
    }
}