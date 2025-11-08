//
// Created by barnab on 05/10/2025.
//

#include "river.h"
#include "pile.h"
namespace Amalena
{
    River::River()
    {
        for (int i =0; i<(Game::getNbPlayers()+2);i++){
            tiles.push_back(Pile::Draw());
        }
    }

    Marilou::Tile& River::giveTile(size_t position)
    {

    }

    bool River::stay1() const
    {
        return tiles.size()==1;
    }

    const size_t River::getPosition(Marilou::Tile* t) const
    {
        for (std::vector<unsigned int>::const_iterator it= tiles.begin();it!=t; it++)
        {

        }
    }
}
