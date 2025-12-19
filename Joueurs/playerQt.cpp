//
// Created by elobo on 10/12/2025.
//
#include "../Gestion/gameQt.h"
#include "../Joueurs/playerQt.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QLabel>
#include <QFormLayout>
using namespace std;

namespace Eloise {

    void PlayerQt::displayBoard() {
        emit boardDisplay("board");
    }

    void PlayerQt::placeTile(const Tile& tile) {
        QWidget* wparent = qobject_cast<QWidget*>(parent());
        bool placed = false;
        while (!placed) {

            QDialog dialog(wparent);
            QFormLayout form(&dialog);
            form.addRow(new QLabel("Position (x,y) and rotation (r)"));
            QList<QLineEdit *> fields;

            QLineEdit *lineEdit = new QLineEdit(&dialog);
            QString label = QString("x :");
            form.addRow(label, lineEdit);
            fields << lineEdit;

            QLineEdit *lineEdit2 = new QLineEdit(&dialog);
            QString label2 = QString("y :");
            form.addRow(label2, lineEdit2);
            fields << lineEdit2;

            QLineEdit *lineEdit3 = new QLineEdit(&dialog);
            QString label3 = QString("r (value between 0 and 5) :");
            form.addRow(label3, lineEdit3);
            fields << lineEdit3;

            QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                       Qt::Horizontal, &dialog);
            form.addRow(&buttonBox);
            connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
            connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

            int x = 0, y = 0, r = 0;
            if (dialog.exec() == QDialog::Accepted) {
                x = fields[0]->text().toInt();
                y = fields[1]->text().toInt();
                r = fields[2]->text().toInt();
            }
            /*
            Ancienne version avec 3 inputs successifs :
            int x = QInputDialog::getInt(wparent, "Place a tile", "x :");
            int y = QInputDialog::getInt(wparent, "Place a tile", "y :");
            int r = QInputDialog::getInt(wparent, "Rotation", "Rotation (0 à 5) :", 0, 0, 5);
            */
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