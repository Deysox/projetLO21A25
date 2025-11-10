
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

int main() {

    using namespace Marilou;

    Cell c(nullptr, Color::GREEN, Type::DISTRICT);
    c.displayTop(cout,2);
    return 0;
}
