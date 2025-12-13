//
// Created by barnab on 13/12/2025.
//

#ifndef PROJETLO21A25_HEXAGON_H
#define PROJETLO21A25_HEXAGON_H

#include <QWidget>
#include <QMainWindow>
#include "cell.h"
#include "board.h"

namespace Barnabe {

    class CellQt : public QWidget {
        int size;
        int w;
        int h;
        static map<Color, pair<QColor, QColor>> colors;

        Color color;
        Type type;
        unsigned int height;
    public:
        CellQt(QWidget* parent, Color c = Color::BLUE, Type t = Type::DISTRICT, unsigned int h = 1, int s = 40);
        void paintEvent(QPaintEvent *event) override;
    };


    class BoardQt : public QWidget {
        int size;

        const Board* board;
        vector<CellQt*> cells;
    public:
        BoardQt(QWidget* parent, const Board* b, int s = 40);
        void empty();
        void update();
        void setBoard(Board* b) {board = b;}
        const Board* getBoard() const {return board;}
    };




}

#endif //PROJETLO21A25_HEXAGON_H