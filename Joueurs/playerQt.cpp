//
// Created by elobo on 10/12/2025.
//
#include "../Gestion/gameQt.h"
#include "../Joueurs/playerQt.h"
#include "../Plateau/QT/boardqt.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QLabel>
#include <QFormLayout>
#include <string>
using namespace std;

namespace Eloise {


    void PlayerQt::displayBoard()
    {
         if (!BoardWidget&&!window)
         {
             window = new QWidget;
             QBoxLayout* layout = new QVBoxLayout(window);

             BoardWidget = new BoardQt(window, board.getBoard());
             layout->addWidget(BoardWidget);
             window->setWindowTitle(
        "A vous de jouer " + QString::fromStdString(this->getName()));
             window->resize(800, 800);
             window->setAttribute(Qt::WA_DeleteOnClose);
             window->show();
         }else
         {
             window->setWindowTitle(
            "A vous de jouer " + QString::fromStdString(this->getName()));
             BoardWidget->updateDisplay();
             window->show();
         }
         }

    void PlayerQt::placeTile(const Tile& tile) {
        QWidget* wparent = qobject_cast<QWidget*>(parent());
        bool placed = false;
        while (!placed) {
            //Dialog qui va permettre de saisir position et rotation
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

            //on récupère des entiers du dialog
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
            //on affecte ces entiers à la position et la rotation
            Position pos(x, y);
            Rotation rotation(r);
            try {
                //on tente de placer la tuile et si recouvrement on ajoute des pierres
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