//
// Created by barnab on 16/12/2025.
//
#include "cellqt.h"

namespace Barnabe {

    CellQt::CellQt(QWidget *parent, Position p, bool l, int s) : QWidget(parent), pos(p), locked(l), size(s), w(size*2), h(std::sqrt(3)*size) {
        setStyleSheet("background-color: rgba(0,0,0,0)");
        setFixedSize(w,w);
        setMouseTracking(true);
    }
    void CellQt::paintEvent(QPaintEvent *event) {
        QPainter hexPainter(this);

        QPen hexPen = pen();
        QBrush hexBrush = brush();
        hexPainter.setBrush(hexBrush);
        hexPainter.setPen(hexPen);

        const QPoint points[6] = {
            QPoint(w/4,0),
            QPoint(3*w/4,0),
            QPoint(w,h/2),
            QPoint(3*w/4,h),
            QPoint(w/4,h),
            QPoint(0,h/2),

        };
        hexPainter.drawPolygon(points,6);



        endPaintEventActions();
    }

    void CellQt::mousePressEvent(QMouseEvent * event) {
        if (!locked) {
            cout << pos << endl;
        }

    }





    map<Color, pair<QColor, QColor>> CellQtFull::colors = {
        {Color::BLUE,{"#559ad6","#1f5a8e"}},
        {Color::RED,{"#db6262","#a03030"}},
        {Color::GREEN,{"#7fe07f","#1f8e1f"}},
        {Color::YELLOW,{"#dbd55e","#a59f2e"}},
        {Color::PURPLE,{"#ae68c1","#8523a0"}},
        {Color::GREY,{"#b7b7b7","#777777"}},
    };

    CellQtFull::CellQtFull(QWidget* parent, Position p, bool l, int s, Color c, Type t, unsigned int hght) :
    CellQt(parent,p,l,s), color(c), type(t), height(hght) {
        label = new QLabel(this);
        label->setText(QString::number(height));
        label->setFont(QFont("monospace",20,600));

        label->move(4*size/5,2*size/5);
    }

    const QBrush CellQtFull::brush() const {
        const QColor penColor = (type == Type::PLACE) ? colors[color].second : colors[color].first;
        QBrush hexBrush(penColor);
        return hexBrush;

    }

    const QPen CellQtFull::pen() const {
        const QColor penColor = (type == Type::PLACE) ? colors[color].first : colors[color].second;
        QPen hexPen(penColor);
        hexPen.setWidth(3);
        return hexPen;
    }

    void CellQtFull::endPaintEventActions() {
        if (underMouse() && !locked) {
            label->setStyleSheet("color:red;");
        } else {
            if (type == Type::PLACE) label->setStyleSheet("color: white;"); else label->setStyleSheet("color: black;");
        }
    }

    CellQtEmpty::CellQtEmpty(QWidget *parent, Position p, bool l, int s) : CellQt(parent,p,l,s){setMouseTracking(true);}


    const QPen CellQtEmpty::pen() const {
        QPen hexPen(Qt::transparent);
        return hexPen;
    }

    const QBrush CellQtEmpty::brush() const {
        QBrush hexBrush(Qt::Dense5Pattern);
        if (underMouse() && !locked) {
            hexBrush.setColor(Qt::red);
        } else {
            hexBrush.setColor(Qt::darkGray);
        }
        return hexBrush;
    }

    void CellQtEmpty::endPaintEventActions() {
        return;
    }

}