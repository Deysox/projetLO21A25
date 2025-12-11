//
// Created by elobo on 10/12/2025.
//
#include "gameQt.h"
#include <QInputDialog>
#include <QMessageBox>
using namespace std;

namespace Barnabe {

    void PlayerQt::displayBoard() {
        emit boardDisplay("board");
    }

    void PlayerQt::placeTile(const Tile& tile) {
        QWidget* wparent = qobject_cast<QWidget*>(parent());
        bool placed = false;
        while (!placed) {
            int x = QInputDialog::getInt(wparent, "Place a tile", "x :");
            int y = QInputDialog::getInt(wparent, "Place a tile", "y :");
            int r = QInputDialog::getInt(wparent, "Rotation", "Rotation (0 à 5) :", 0, 0, 5);

            Position pos(x, y);
            Rotation rotation(r);

            try {
                addStones(board.place(&tile, pos, rotation));
                placed = true;
            }
            catch (const PlacementException& pe) {
                QMessageBox::warning(wparent, "Error", pe.what());
            }
            catch (const TileException& te) {
                QMessageBox::warning(wparent, "Error", te.what());
            }
        }
    }
}