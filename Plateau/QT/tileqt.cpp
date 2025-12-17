//
// Created by barnab on 17/12/2025.
//
#include "tileqt.h"

namespace Barnabe {
    void ClassicTileQt::draw() {
        const Cell* c = tile->getCell(1);
        CellQtFull* cqt = new CellQtFull(this,Position(0,0),true,size,c->getColor(),c->getType(),0);
        cqt->move(0,0);
        cells.push_back(cqt);

        c = tile->getCell(0);
        cqt = new CellQtFull(this,Position(0,0),true,size,c->getColor(),c->getType(),0);
        cqt->move(0,std::sqrt(3)*size);
        cells.push_back(cqt);

        c = tile->getCell(2);
        cqt = new CellQtFull(this,Position(0,0),true,size,c->getColor(),c->getType(),0);
        cqt->move(3*size/2,std::sqrt(3)*size/2);
        cells.push_back(cqt);




    }


}