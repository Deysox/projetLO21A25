//
// Created by barnab on 05/10/2025.
//

#ifndef PROJETLO21A25_RIVER_H
#define PROJETLO21A25_RIVER_H
#include <vector>
#include <iostream>
#include "tile.h"
using namespace std;
using namespace Marilou;
//namespace Marilou {//temporaire
//    class Tile;
//}
namespace Amalena {
    class River{
        vector<Tile*> tiles;
        River();//friend avec ctrl?? ou jeu
        ~River();//friend jeu ou ctrl reflechir si op à faire : désallouer le vecteur
        River(const River& f)=delete;
        River& operator=(River& f)=delete;
    public:
        Tile& giveTile(size_t position);
        bool stay1()const;
        const size_t getPosition(Tile* t) const;// et donc par repercussion le cout en pierres
        //réfléchir à qui gère les transactions + création d'une erreur si pierre insufissantes juste une cdtion
        //??alimenter s'auto alimente qd reste 1
        friend class Game;
    };
}
ostream& operator<<(ostream& f, const Amalena::River& r);
#endif //PROJETLO21A25_RIVER_H