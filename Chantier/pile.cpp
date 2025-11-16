//
// Created by barnab on 05/10/2025.
//
#include "pile.h"
#include <vector>
using namespace std;
namespace Amalena
{
    Marilou::Tile* Pile::Draw()
    {

        if (isEmpty()) throw PileException("Empty pile");

        Marilou::Tile* t = tiles.back();
        tiles.pop_back();
        return t;
    }//en admettant que les tuiles ont aléatoirement été placé dans le vecteur
    //que pour une tuile réfléchir à verif prendre plusieur à la fois

    bool Pile::isEmpty()const
    {
        return tiles.empty();
    }



}
