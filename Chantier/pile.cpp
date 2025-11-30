
#include "pile.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
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

    Pile::Pile(Eloise::Deck& d): deck(d)
    {
        tiles=d.getTiles();
        //utilisation de l'algorithme de mélange aléatoire pour randomiser l'ordre des tuiles
        //source :https://en.cppreference.com/w/cpp/algorithm/random_shuffle.html
        std::random_device rd;
        std::mt19937 g(rd());
        shuffle(tiles.begin(), tiles.end(), g);
    }

    bool Pile::isEmpty()const
    {
        return tiles.empty();
    }
    Pile::~Pile(){
        cout<<"destruction pile";
    }



}
