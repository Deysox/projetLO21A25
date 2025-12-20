//
// Created by barnab on 13/12/2025.
//
#include "boardqt.h"

#include <cmath>
#include <QPainter>
#include <QPoint>
#include <QLabel>
#include <QMouseEvent>

namespace Barnabe {

    void BoardQt::empty() {
        for (pair<Position, CellQt*> p : cells) delete p.second;
        cells.clear();
    }

    void BoardQt::draw() {
        empty();
        const Position ctl = item->getCorners().first;
        const int w = size*2; // Calcul de la largeur
        const int h = std::sqrt(3)*size; // Calcul de la hauteur
        const int x_offset = (ctl.x()-1)*w; // Décalage des positions par rapport au coin supérieur
        const int y_offset = -(ctl.y()+1)*h;

        for (const pair<Position, pair<const Cell*, unsigned int>> p : *item) { // Itération sur les cases du plateau
            Position pos = p.first;
            const Cell* cell = p.second.first;
            const unsigned int hght = p.second.second;

            // Création du widget case
            CellQt* cell_qt = new CellQtFull(this,pos,false,40,cell->getColor(),cell->getType(),hght);

            // Calcul des coordonnées en pixel à partir de la Position
            const int movex = pos.x()*3*w/4-x_offset;
            int movey = -pos.y()*h-y_offset;

            // Décalage de hauteur pour les colonnes impaires
            if (pos.x()%2 != 0) movey += h/2;
            cell_qt->move(movex,movey);

            cells[pos] = cell_qt; // Assignation dans la map

            for (const Position& subpos : pos) { // Itération sur les voisins
                const auto finder = cells.find(subpos);
                if (finder == cells.end()) { // S'il n'y a pas déjà une case, création d'un emplacement de contour
                    CellQt* sub_cell_qt = new CellQtEmpty(this,subpos,false,40);

                    // Calcul des coordonnées en pixel à partir de la Position
                    const int submovex = subpos.x()*3*w/4-x_offset;
                    int submovey = -subpos.y()*h-y_offset;

                    if (subpos.x()%2 != 0) submovey += h/2;
                    sub_cell_qt->move(submovex,submovey);
                    cells[subpos] = sub_cell_qt; // Assignation dans la map
                }
            }
        }
        update();
    }







}