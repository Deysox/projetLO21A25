//
// Created by barnab on 17/12/2025.
//

#ifndef AKROPOLIS_TILEQT_H
#define AKROPOLIS_TILEQT_H

#include "cellqt.h"
#include "containerqt.h"
#include "tile.h"

namespace Barnabe {
    class TileQt : public ContainerQt {
    protected:
        vector<CellQtFull*> cells;
        const Tile* tile;
    public:
        TileQt(QWidget* parent, const Tile* t, int s = 40) : ContainerQt(parent, s), tile(t) {}

        void empty() {
            for (const CellQtFull* vec : cells) delete vec;
            cells.clear();
        }

        //void transparencyOn();
        //void transparencyOff();
    };

    class ClassicTileQt : public TileQt {
    public:
        ClassicTileQt(QWidget* parent, const ClassicTile* ct, int s = 40) : TileQt(parent, ct, s) {
            setFixedSize(7*size/2,2*std::sqrt(3)*size);
            updateDisplay();
        }
        void setTile(const ClassicTile *ct) {tile = ct;}
        const Tile* getTile() const {return tile;}
        void draw() override;
    };


}

#endif //AKROPOLIS_TILEQT_H