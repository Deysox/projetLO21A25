
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

int main() {
    using namespace Barnabe;

    BoardManager bm;


    ClassicTile* st = new ClassicTile(Color::RED,Type::DISTRICT,Color::GREY,Type::QUARRY,Color::GREEN,Type::DISTRICT);

    bm.place(st,Position(1,1),0);
    bm.place(st,Position(0,1),1);

    bm.place(st,Position(10,10),4,true);

    cout << bm;

    return 0;
}
