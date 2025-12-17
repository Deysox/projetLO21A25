//
// Created by barnab on 16/12/2025.
//

#ifndef AKROPOLIS_CELLQT_H
#define AKROPOLIS_CELLQT_H



#include "../../Utilitaires/position.h"
#include "../../Tuiles/cell.h"

#include <QWidget>
#include <QMainWindow>
#include <QMouseEvent>

#include <QLabel>
#include <QBrush>
#include <QPen>
#include <QPainter>

namespace Barnabe {
    class CellQt : public QWidget {
    protected:
        int size;
        int w;
        int h;

        Position pos;

        bool locked;

    public:
        CellQt(QWidget* parent, Position p, bool l = false, int s = 40);
        virtual ~CellQt() = default;
        void paintEvent(QPaintEvent *event) override;


        virtual const QBrush brush() const = 0;
        virtual const QPen pen() const = 0;

        virtual void endPaintEventActions() = 0;

        void lock() {locked = true;}
        void unlock() {locked = false;}



    };


    class CellQtFull : public CellQt {
        static map<Color, pair<QColor, QColor>> colors;
        static map<Color, string> colorText;
        static map<Color, string> placeText;
        Color color;
        Type type;
        unsigned int height;
        QLabel* label;
    public:
        CellQtFull(QWidget* parent, Position p, bool l = false, int s = 40, Color c = Color::BLUE, Type t = Type::DISTRICT, unsigned int hght = 0);

        const QBrush brush() const override;
        const QPen pen() const override;

        void endPaintEventActions() override;

    };

    class CellQtEmpty : public CellQt {
    public:
        CellQtEmpty(QWidget* parent, Position p, bool l = false, int s = 40);

        const QBrush brush() const override;
        const QPen pen() const override;
        void endPaintEventActions() override;
    };
}

#endif //AKROPOLIS_CELLQT_H