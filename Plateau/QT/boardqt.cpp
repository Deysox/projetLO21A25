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
    BoardQt::BoardQt(QWidget *parent, const Board *b, int s) : ContainerQt(parent,s), board(b) {updateDisplay();}

    void BoardQt::empty() {
        for (auto it = cells.begin(); it != cells.end(); it++) delete it->second;
        cells.clear();
    }

    void BoardQt::draw() {
        empty();
        Position ctl = board->getCorners().first;
        int w = size*2;
        int h = std::sqrt(3)*size;
        int x_offset = (ctl.x()-1)*w;
        int y_offset = -(ctl.y()+1)*h;

        for (auto it = board->cbegin(); it != board->cend(); it++) {
            Position pos = it->first;
            const Cell* cell = it->second.first;
            unsigned int hght = it->second.second;

            CellQt* cell_qt = new CellQtFull(this,pos,false,40,cell->getColor(),cell->getType(),hght);
            int movex = pos.x()*3*w/4-x_offset;
            int movey = -pos.y()*h-y_offset;

            if (pos.x()%2 != 0) movey += h/2;
            cell_qt->move(movex,movey);
            cells[pos] = cell_qt;

            for (auto it_pos = pos.begin(); it_pos != pos.end(); it_pos++) {
                Position subpos(*it_pos);

                auto finder = cells.find(subpos);
                if (finder == cells.end()) {
                    CellQt* sub_cell_qt = new CellQtEmpty(this,pos,false,40);
                    int submovex = subpos.x()*3*w/4-x_offset;
                    int submovey = -subpos.y()*h-y_offset;

                    if (subpos.x()%2 != 0) submovey += h/2;
                    sub_cell_qt->move(submovex,submovey);
                    cells[subpos] = sub_cell_qt;
                }

            }
        }


        update();
    }







}