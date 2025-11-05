//
// Created by barnab on 13/10/2025.
//

#ifndef PROJETLO21A25_ROTATION_H
#define PROJETLO21A25_ROTATION_H

#include "exceptions.h"
#include "position.h"

namespace Barnabe {


    class Rotation {
        int rot;
    public:
        Rotation(int r = 0) : rot(r%6) {};

        int value() const {return rot;}

        Rotation operator+(const Rotation&) {return Rotation((rot+1)%6 == 0);};
        Rotation operator-(const Rotation&) {return Rotation((rot-1)%6==0);}
        Rotation operator++() {rot++; return *this;}
        Rotation operator++(int) {int old = rot; rot++; return Rotation(old);};
        bool operator==(const Rotation& r) {return rot == r.rot;};
        bool operator!=(const Rotation& r) {return rot != r.rot;}
    };
}


#endif //PROJETLO21A25_ROTATION_H