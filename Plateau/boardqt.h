//
// Created by barnab on 13/12/2025.
//

#ifndef PROJETLO21A25_HEXAGON_H
#define PROJETLO21A25_HEXAGON_H

#include <QWidget>
#include <QMainWindow>
#include <QMouseEvent>
#include "../Tuiles/cell.h"
#include "board.h"
#include <QLabel>

namespace Barnabe {

    class CellQt : public QWidget {
        int size;
        int w;
        int h;
        static map<Color, pair<QColor, QColor>> colors;

        Position pos;
        Color color;
        Type type;
        unsigned int height;

        QLabel* label;

        bool locked;
    public:
        CellQt(QWidget* parent, Position p, Color c = Color::BLUE, Type t = Type::DISTRICT, unsigned int h = 1, int s = 40);
        void paintEvent(QPaintEvent *event) override;
        void mousePressEvent ( QMouseEvent * event ) override;

        void lock() {locked = true;}
        void unlock() {locked = false;}


    };


    class BoardQt : public QWidget {
        int size;

        const Board* board;
        vector<CellQt*> cells;
    public:
        BoardQt(QWidget* parent, const Board* b, int s = 40);
        void empty();
        void updateDisplay();
        void setBoard(Board* b) {board = b;}
        const Board* getBoard() const {return board;}

        void lock() {for (auto it = cells.begin(); it != cells.end(); it++) (*it)->lock();}
        void unlock() {for (auto it = cells.begin(); it != cells.end(); it++) (*it)->unlock();}

    };




}

#endif //PROJETLO21A25_HEXAGON_H