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
         * constucteur de widget river
         * @param parent
         * @param r river&
         */
        riverQT(QWidget* parent,River& r);
        /**
         * destructeur
         */
        ~riverQT() override =default;
        /**
         * mise à jour de la rivière
         */
        void updateDisplay();


    };
}

#endif //PROJETLO21A25_RIVERQT_H