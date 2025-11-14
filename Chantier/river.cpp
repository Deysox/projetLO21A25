//
// Created by barnab on 05/10/2025.
//

#include "river.h"
#include "pile.h"
#include "game.h"

namespace Amalena
{
    River::River(size_t nb, Pile& pile):max_tiles(nb), pile(pile) //parmaetre du constructeur ou un attribut nb tuiles
    {
        River::fillriver();
        // for (int i =0; i<(max_tiles);i++){
        //     tiles.push_back(pile.Draw());
        // }
    }



    void River::fillriver()
    {
        while (tiles.size()<max_tiles) tiles.push_back(pile.Draw());
    }

    Marilou::Tile& River::giveTile(size_t position)
    {
        if (position>tiles.size()) throw std::out_of_range("position out of range dans la rivière");
        Tile* t=tiles[position-1];
        tiles.erase(tiles.begin()+(position-1));
        if (stay1()) fillriver();
        return *t;

    }

    bool River::stay1() const
    {
        return tiles.size()==1;
    }

    size_t River::getPosition(const Tile* t) const
    {
        size_t position=0;// n'existe pas
        for (auto it= tiles.begin() ;it!=tiles.end(); ++it)
        {   ++position;
            if (*it==t) return position;
        }
        return 0;
        //if (position==1000)throw riverException("inexistant"); OU retour d'un chiffre abérant
    }
    River::~River()
    {
        cout<<"destruction river";
        //gérer sauvegarde
    }

}
