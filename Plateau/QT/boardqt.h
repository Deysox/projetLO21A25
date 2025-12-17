//
// Created by barnab on 13/12/2025.
//

#ifndef PROJETLO21A25_HEXAGON_H
#define PROJETLO21A25_HEXAGON_H

#include "../../Tuiles/tile.h"
#include "../../Plateau/board.h"
#include "cellqt.h"

#include <QWidget>
#include "containerqt.h"
#include "tileqt.h"


namespace Barnabe {


    class BoardQt : public ContainerQt {
        const Board* board;
        unordered_map<Position, CellQt*, PositionHasher> cells;
    public:
        BoardQt(QWidget* parent, const Board* b, int s = 40);
        void empty() override;
        void draw() override;
        void setBoard(Board* b) {board = b;}
        const Board* getBoard() const {return board;}

        void lock() {for (auto it = cells.begin(); it != cells.end(); it++) it->second->lock();}
        void unlock() {for (auto it = cells.begin(); it != cells.end(); it++) it->second->unlock();}


    };




}

#endif //PROJETLO21A25_HEXAGON_H