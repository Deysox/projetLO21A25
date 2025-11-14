//
// Created by barnab on 05/10/2025.
//
#include "pile.h"
#include <vector>
#include <iostream>
using namespace std;
namespace Amalena
{
    Marilou::Tile* Pile::Draw()
    {
        if (!isEmpty())
        {
            //throw PileException("Empty pile");

            Marilou::Tile* t = tiles.back();
            tiles.pop_back();
            return t;
        }else
        {
            printf("pioche vide, distribution impossible");
            return nullptr;
        }
    }
    bool Pile::isEmpty()const
    {
        return tiles.empty();
    }
    Pile::~Pile(){
        cout<<"destruction pile";
    }



}
