//
// Created by GAUTIER--BONNEAU on 17/12/2025.
//
#include <QWidget>
#include "../Chantier/river.h"
#include "../Chantier/riverQT.h"
#include "../Plateau/QT/tileqt.h"
#include <QHBoxLayout>
namespace Amalena
{
    riverQT::riverQT(QWidget* parent, River& r):QWidget(parent),river(r)
    {
        QHBoxLayout* layout = new QHBoxLayout(this);

       for (auto it=river.begin();it!=river.end();++it)
        {
            Barnabe::Tile& t=*it;
           if (ClassicTile* ct=dynamic_cast<ClassicTile*> (&t))
           {
               layout->addWidget(new Barnabe::ClassicTileQt(this,ct));
           }

        }



    };
     void   riverQT::updateDisplay()
       {
         auto* layout =this->layout();
         QLayoutItem *child;
         //suppresion des widgets présents dans le layout
         while ((child = layout->takeAt(0)) != nullptr) {

             delete child->widget();
             delete child;
         }
        //ajout des nouveau widgets
         for (auto it=river.begin();it!=river.end();++it)
         {
             Barnabe::Tile& t=*it;
             if (ClassicTile* ct=dynamic_cast<ClassicTile*> (&t))
             {
                 layout->addWidget(new Barnabe::ClassicTileQt(this,ct));
             }
         }
        layout->invalidate();
        update();

    };

}