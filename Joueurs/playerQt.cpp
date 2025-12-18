//
// Created by elobo on 10/12/2025.
//
#include "../Gestion/gameQt.h"
#include "../Joueurs/playerQt.h"
#include <QInputDialog>
#include <QMessageBox>
using namespace std;

namespace Eloise {

    void PlayerQt::displayBoard() {
        emit boardDisplay("board");
    }

    void PlayerQt::placeTile(const Tile& tile) {
        //mandatory cast because we need a QWidget for the QInputDialog
        QWidget* wparent = qobject_cast<QWidget*>(parent());
        bool placed = false;
        while (!placed) {
            int x = QInputDialog::getInt(wparent, "Place a tile", "x :");
            int y = QInputDialog::getInt(wparent, "Place a tile", "y :");
            int r = QInputDialog::getInt(wparent, "Rotation", "Rotation (0 à 5) :", 0, 0, 5);

            Position pos(x, y);
            Rotation rotation(r);

            try {
                //place returns a int
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