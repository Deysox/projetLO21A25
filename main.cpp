
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
    using namespace Marilou;
    using namespace Barnabe;

    Cell c1 = Cell(nullptr,Color::BLUE,Type::DISTRICT);
    Cell c2 = Cell(nullptr,Color::GREEN,Type::DISTRICT);
    Cell c3 = Cell(nullptr,Color::YELLOW,Type::PLACE);
    Cell c4 = Cell(nullptr, Color::GREY, Type::QUARRY);

    Board b;
    b.setCell(0,0,1,&c1);
    b.setCell(0,1,1,&c2);
    b.setCell(-1,1,2,&c2);
    b.setCell(1,1,3,&c3);
    b.setCell(-1,0,1,&c4);
    b.setCell(2,1,1,&c2);
    b.setCell(2,2,2,&c2);
    b.setCell(0,-1,3,&c2);
    b.setCell(0,-2,3,&c3);
    b.setCell(-1,-2,1,&c4);
    //b.setCell(-30,-10,1,&c4);

    cout << b;

    return 0;
}
