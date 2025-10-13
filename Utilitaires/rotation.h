//
// Created by barnab on 13/10/2025.
//

#ifndef PROJETLO21A25_ROTATION_H
#define PROJETLO21A25_ROTATION_H

#include "exceptions.h"

namespace Barnabe {
    class Rotation {
        int rotation;
    public:
        Rotation(int rot) : rotation(rot) { if (rot < 0 || rot > 5) throw PlateauException("Rotation Invalide : entrez un nombre entre 0 et 5");}

        Rotation operator+(const Rotation&);
        Rotation operator-(const Rotation&);
        Rotation operator==(const Rotation&);
        Rotation operator!=(const Rotation&);
    };
}


#endif //PROJETLO21A25_ROTATION_H