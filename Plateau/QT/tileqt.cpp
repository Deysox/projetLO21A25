//
// Created by barnab on 17/12/2025.
//
#include "tileqt.h"

namespace Barnabe {
    void ClassicTileQt::draw() {
        // Deuxième case (celle du haut)
        const Cell* c = tile->getCell(1);
        // Création de la CellQtFull
        CellQtFull* cqt = new CellQtFull(this,Position(0,0),true,size,c->getColor(),c->getType(),0);
        // Placement dans le widget
        cqt->move(0,0);
        // Ajout dans le vecteur pour la gestion du cycle de vie.
        cells.push_back(cqt);

        // Première case (celle du bas)
        c = tile->getCell(0);
        cqt = new CellQtFull(this,Position(0,0),true,size,c->getColor(),c->getType(),0);
        cqt->move(0,std::sqrt(3)*size);
        cells.push_back(cqt);

        // Troisième case (celle de droite)
        c = tile->getCell(2);
        cqt = new CellQtFull(this,Position(0,0),true,size,c->getColor(),c->getType(),0);
        cqt->move(3*size/2,std::sqrt(3)*size/2);
        cells.push_back(cqt);
    }
}