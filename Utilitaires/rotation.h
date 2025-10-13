//
// Created by barnab on 13/10/2025.
//

#ifndef PROJETLO21A25_ROTATION_H
#define PROJETLO21A25_ROTATION_H

#include "exceptions.h"
#include "exceptions.h"

namespace Barnabe {
    class Rotation {
        int rot;
    public:
        Rotation(int r = 0);

        Rotation operator+(const Rotation&);
        Rotation operator-(const Rotation&);
        Rotation operator++();
        Rotation operator++(int);
        bool operator==(const Rotation&);
        bool operator!=(const Rotation&);
    };
}


#endif //PROJETLO21A25_ROTATION_H