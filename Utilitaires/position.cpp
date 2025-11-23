//
// Created by barnab on 05/11/2025.
//
#include "position.h"
#include "rotation.h"

namespace Barnabe {
    Position Position::operator+(const Rotation& r) const {
        Position output;
        int parity = posX%2; // Les coordonnées voisines changent selon la parité de x
        switch (r.value()) {
            case 0:
                output = Position(posX,posY+1); // Universel
                break;
            case 1:
                output = Position(posX+1,posY+1-parity); // (x+1;y+1) si x pair, (x+1;y) si x impair
                break;
            case 2:
                output = Position(posX+1,posY-parity); // (x+1;y) si x pair, (x+1;y-1) si x impair
                break;
            case 3:
                output = Position(posX,posY-1); // Universel
                break;
            case 4:
                output = Position(posX-1,posY-parity); // (x-1;y) si x pair, (x-1;y-1) si x impair
                break;
            case 5:
                output = Position(posX-1,posY+1-parity); // (x-1;y+1) si x pair, (x-1;y) si x impair
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

ostream& operator<<(ostream& f, const Barnabe::Position& p) {
    string out = "(" + to_string(p.x()) + ";" + to_string(p.y()) +")";
    f << out;
    return f;
}