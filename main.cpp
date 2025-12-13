
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



#include <QApplication>

#include "boardmanager.h"
#include "boardqt.h"



int main(int argc, char* argv[])
{
    QApplication app(argc, argv);


    Barnabe::BoardManager bm;
    Barnabe::BoardQt bqt(nullptr,bm.getBoard());
    bqt.setFixedSize(500,500);

    bqt.show();

    return app.exec();
}

