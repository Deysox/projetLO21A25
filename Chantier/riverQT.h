//
// Created by GAUTIER--BONNEAU on 17/12/2025.
//

#ifndef PROJETLO21A25_RIVERQT_H
#define PROJETLO21A25_RIVERQT_H
#include <QWidget>

namespace Amalena
{

    class riverQT :public QWidget
    {
        River& river;



    public:
        /**
         *
         * @param parent
         * @param r
         */
        riverQT(QWidget* parent,River& r);
        ~riverQT() override =default;
        void updateDisplay();

        //verif okay par autre => mà jour riverqt
        //refresh riverQT or display

    };
}

#endif //PROJETLO21A25_RIVERQT_H