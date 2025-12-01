
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

    int i = 1;
    for (auto it = vec.begin(); it != vec.end(); it++) {
        cout << i++ << endl;
        cout << *(*it);

    }

    BoardManager bm;
    bm.place(vec[0],Position(1,1),Rotation(0));
    bm.place(vec[1],Position(0,2),Rotation(4));
    bm.place(vec[2],Position(0,1),Rotation(0));

    cout << bm;




    return 0;
}
