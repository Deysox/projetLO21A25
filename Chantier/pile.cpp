
#include "pile.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

#include "deck.h"
#include "tile.h"
using namespace std;
namespace Amalena
{
    Barnabe::Tile* Pile::Draw()
    {
        if (!isEmpty())
        {
            //throw PileException("Empty pile");

            Barnabe::Tile* t = tiles.back();
            tiles.pop_back();
            return t;
        }else
        {
            printf("pioche vide, distribution impossible");
            return nullptr;
        }
    }

    Pile& Pile::operator=(const Pile& p) {
        if (this!=&p) {
            this->tiles = p.tiles;
            this->deck = p.deck;
        }
        return *this;
    }

    Pile::Pile(Eloise::Deck& d): deck(d)
    {
        tiles={};
        //tiles=d.getTiles();//proposition à réétudier
        for (auto t : d.getTiles()) {
            tiles.push_back(static_cast<Barnabe::Tile*>(t));
        }
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
