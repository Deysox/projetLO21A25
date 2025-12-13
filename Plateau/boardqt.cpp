//
// Created by barnab on 13/12/2025.
//
#include "boardqt.h"

#include <cmath>
#include <QPainter>
#include <QPoint>

namespace Barnabe {


    map<Color, pair<QColor, QColor>> CellQt::colors = {
        {Color::BLUE,{"#559ad6","#1f5a8e"}},
        {Color::RED,{"#db6262","#a03030"}},
        {Color::GREEN,{"#7fe07f","#1f8e1f"}},
        {Color::YELLOW,{"#dbd55e","#a59f2e"}},
        {Color::PURPLE,{"#ae68c1","#8523a0"}},
        {Color::GREY,{"#b7b7b7","#777777"}},
    };

    CellQt::CellQt(QWidget *parent, Color c, Type t, unsigned int hght, int s) :
    QWidget(parent), color(c), type(t), height(hght), size(s), w(size*2), h(std::sqrt(3)*size) {
        setStyleSheet("background-color: rgba(0,0,0,0)");
        setFixedSize(w,w);

    }

    void CellQt::paintEvent(QPaintEvent *event) {
        QPainter hexPainter(this);

        QPen hexPen(colors[color].second);
        QBrush hexBrush(colors[color].first);
        hexPen.setWidth(3);


        hexPainter.setPen(hexPen);
        hexPainter.setBrush(hexBrush);

        const QPoint points[6] = {
            QPoint(w/4,0),
            QPoint(3*w/4,0),
            QPoint(w,h/2),
            QPoint(3*w/4,h),
            QPoint(w/4,h),
            QPoint(0,h/2),

        };
        hexPainter.drawPolygon(points,6);

    }

    BoardQt::BoardQt(QWidget *parent, const Board *b, int s) : QWidget(parent), board(b), size(s) {
        setStyleSheet("background-color:#e0e0e0;");
        update();

    }

    void BoardQt::empty() {
        for (auto it = cells.begin(); it != cells.end(); it++) delete *it;
        cells.clear();
    }

    void BoardQt::update() {
        empty();
        Position ctl = board->getCorners().first;
        int w = size*2;
        int h = std::sqrt(3)*size;
        int x_offset = ctl.x()*w;
        int y_offset = -ctl.y()*h;



        for (auto it = board->cbegin(); it != board->cend(); it++) {
            Position pos = it->first;
            const Cell* cell = it->second.first;
            unsigned int hght = it->second.second;

            CellQt* cell_qt = new CellQt(this,cell->getColor(), cell->getType(),hght);
            int movex = pos.x()*3*w/4-x_offset;
            int movey = -pos.y()*h-y_offset;

            if (pos.x()%2 != 0) movey += h/2;
            cell_qt->move(movex,movey);
            cells.push_back(cell_qt);
        }
    }




}