//
// Created by barnab on 16/12/2025.
//
#include "cellqt.h"
#include <QToolTip>
#include <sstream>

namespace Barnabe {

    CellQt::CellQt(QWidget *parent, Position p, bool l, int s) : QWidget(parent), pos(p), locked(l), size(s), w(size*2), h(std::sqrt(3)*size) {
        setStyleSheet("QWidget{background-color: rgba(0,0,0,0);}QToolTip{background-color:rgba(255,255,255,1);padding:1px;border:none;border-radius:3px;font-family:monospace;}");
        setFixedSize(w,w);
        setMouseTracking(true);
        setToolTip(QString::fromStdString(pos.toString()));

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

        }; // Points du tracé sous forme d'hexagone.
        hexPainter.drawPolygon(points,6);
        endPaintEventActions();
    }

    // ===== Maps pour les couleurs =====
    map<Color, pair<QColor, QColor>> CellQtFull::colors = {
        {Color::BLUE,{"#559ad6","#1f5a8e"}},
        {Color::RED,{"#db6262","#a03030"}},
        {Color::GREEN,{"#7fe07f","#1f8e1f"}},
        {Color::YELLOW,{"#dbd55e","#a59f2e"}},
        {Color::PURPLE,{"#ae68c1","#8523a0"}},
        {Color::GREY,{"#b7b7b7","#777777"}},
    };

    map<Color, string> CellQtFull::colorText = {
        {Color::BLUE,"Habitations"},
        {Color::YELLOW,"Marché"},
        {Color::RED,"Casernes"},
        {Color::PURPLE,"Temple"},
        {Color::GREEN,"Jardins"},
    };

    map<Color, string> CellQtFull::placeText = {
        {Color::BLUE,"(*)"},
        {Color::YELLOW,"(**)"},
        {Color::RED,"(**)"},
        {Color::PURPLE,"(**)"},
        {Color::GREEN,"(***)"},
    };


    CellQtFull::CellQtFull(QWidget* parent, Position p, bool l, int s, Color c, Type t, unsigned int hght) :
    CellQt(parent,p,l,s), color(c), type(t), height(hght) {
        if (height > 0) { // Affichage de la hauteur
            label = new QLabel(this);
            label->setText(QString::number(height));
            label->setFont(QFont("monospace",20,600));
            label->move(4*size/5,2*size/5);
        }

        stringstream ss; // Génération du Tooltip
        ss << "Position : "<<pos.toString()<<"\nHauteur : "<<to_string(height)<<"\n";
        if (type == Type::DISTRICT) {
            ss << "Quartier " << colorText[color];
        } else if (type == Type::PLACE) {
            ss << "Place " << colorText[color] << " " << placeText[color];
        } else {
            ss << "Carrière";
        }
        setToolTip(QString::fromStdString(ss.str()));




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
        if (height > 0) {
            if (underMouse() && !locked) {
                label->setStyleSheet("color:red;");
            } else {
                if (type == Type::PLACE) label->setStyleSheet("color: white;"); else label->setStyleSheet("color: black;");
            }
        }
    }



    CellQtEmpty::CellQtEmpty(QWidget *parent, Position p, bool l, int s) : CellQt(parent,p,l,s) {
        setToolTip(QString::fromStdString("Position : "+pos.toString())); // Génération du Tooltip
    }


    const QPen CellQtEmpty::pen() const {
        QPen hexPen(Qt::transparent);
        return hexPen;
    }

    const QBrush CellQtEmpty::brush() const {
        QBrush hexBrush(Qt::Dense6Pattern);
        if (underMouse() && !locked) {
            hexBrush.setColor(Qt::red);
        } else {
            hexBrush.setColor(Qt::darkGray);
        }
        return hexBrush;
    }



}