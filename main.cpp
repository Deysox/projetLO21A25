#include <iostream>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QString>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QApplication>

#include "Plateau/boardmanager.h"
#include "Plateau/QT/boardqt.h"
#include "Gestion/menu.h"
/*
int main(int argc, char* argv[])
{
    using namespace Barnabe;
    QApplication app(argc, argv);

    Barnabe::ClassicTile* t = new ClassicTile(Color::BLUE,Type::DISTRICT,Color::RED,Type::DISTRICT,Color::GREEN,Type::DISTRICT);
    Barnabe::ClassicTile* t2 = new ClassicTile(Color::PURPLE,Type::PLACE,Color::YELLOW,Type::DISTRICT,Color::RED,Type::PLACE);
    Barnabe::BoardManager bm;

    bm.place(t,Position(1,1),Rotation(0));
    bm.place(t2,Position(0,-2),Rotation(0));
    bm.place(t,Position(0,0),Rotation(0));

    Barnabe::BoardQt bqt(nullptr,bm.getBoard());


    bqt.setFixedSize(500, 500);
    bqt.setStyleSheet("background-color:rgba(255,255,255,1);");

    bqt.show();
    return app.exec();
}
*/
/*
#include <QApplication>

#include "boardmanager.h"
#include "boardqt.h"



int main(int argc, char* argv[])
{
    using namespace Barnabe;
    QApplication app(argc, argv);

    Barnabe::ClassicTile t1(Color::BLUE,Type::DISTRICT,Color::PURPLE,Type::PLACE,Color::GREEN,Type::DISTRICT);
    Barnabe::ClassicTile t2(Color::YELLOW,Type::DISTRICT,Color::RED,Type::DISTRICT,Color::GREEN,Type::PLACE);
    Barnabe::ClassicTile t3(Color::YELLOW,Type::PLACE,Color::GREY,Type::QUARRY,Color::PURPLE,Type::DISTRICT);

    Barnabe::BoardManager bm;
    bm.place(&t1,Position(1,1),0);
    bm.place(&t2,Position(-1,1),4);
    bm.place(&t3,Position(0,-2),5);
    bm.place(&t3,Position(-2,-1),4);


    Barnabe::BoardQt bqt(nullptr,bm.getBoard());
    bqt.setFixedSize(500,500);



    bm.place(&t1,Position(-1,0),3);
    bqt.updateDisplay();

    bqt.show();

    return app.exec();
}
*/
/*
#include "Gestion/menu2.h"
int main() {
    Eloise::Menu menu;
}
*/

#include "Gestion/menu.h"
#include "menu2.h"
#include <QApplication>
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Eloise::Menu menu;
    return app.exec();
}
