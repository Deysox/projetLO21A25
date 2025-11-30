
#include <iostream>
/*#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QString>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Menu menu;
    menu.setFixedSize(500, 400);
    menu.show();
    return app.exec();
}*/

#include "Tuiles/cell.h"
#include "Tuiles/tile.h"
#include "Plateau/board.h"
#include "Plateau/boardmanager.h"
#include "deck.h"

int main() {
    using namespace Barnabe;

    Eloise::Deck d(2);

    const vector<ClassicTile*> vec = d.getTiles();
    for (auto it = vec.begin(); it != vec.end(); it++) {
        cout << *(*it);
    }




    return 0;
}
