
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
#include "pile.h"
#include "menu2.h"
#include "river.h"
#include <QApplication>
#include "boardqt.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    ClassicTile t1(Color::YELLOW,Type::DISTRICT,Color::GREEN,Type::DISTRICT,Color::RED,Type::DISTRICT);

    BoardManager bm;
    bm.place(&t1,Position(1,1),0);
    bm.place(&t1,Position(0,-2),4);

    BoardQt bqt(nullptr, bm.getBoard());
    bqt.setFixedSize(500,500);

    bm.place(&t1,Position(-1,1),5);
    vector<Position> poss = t1.calculatePositions(Position(-1,1),5);
    for (auto it = poss.begin(); it != poss.end(); it++) cout << *it << endl;
    bqt.update();



    bqt.show();

    Rotation r = Rotation(5);
    cout << Position(-1,1)+(r) << endl;


    return app.exec();
}
