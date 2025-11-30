
#include "pile.h"
#include <vector>
#include <iostream>
using namespace std;
namespace Amalena
{
    Barnabe::ClassicTile* Pile::Draw()
    {
        if (!isEmpty())
        {
            //throw PileException("Empty pile");

            Barnabe::ClassicTile* t = tiles.back();
            tiles.pop_back();
            return t;
        }else
        {
            printf("pioche vide, distribution impossible");
            return nullptr;
        }
    }

    Pile::Pile(Deck& d): deck(d), tiles(d.getTiles())
    {
    }

    bool Pile::isEmpty()const
    {
        return tiles.empty();
    }
    Pile::~Pile(){
        cout<<"destruction pile";
    }



}
