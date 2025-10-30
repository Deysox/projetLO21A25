//
// Created by barnab on 05/10/2025.
//

#ifndef PROJETLO21A25_PILE_H
#define PROJETLO21A25_PILE_H
#include <vector>
using namespace std;
//using namespace Marilou;
namespace Marilou {//temporaire
    class Tile;
}
namespace Amalena {
    class Pile{
        vector <Marilou::Tile*> tuiles;

        Pile(vector <Marilou::Tile*> t);
        ~Pile();//friend jeu ou ctrl reflechir si op à faire : désallouer le vecteur
        Pile(const Pile& p)=delete;//et si retour en arrière?
        Pile& operator=(Pile& p)=delete;//? utilisation si memo retour arrière
        Marilou::Tile* Draw();//piocher  ?? creéer une facon dans piocher plusieurs ou utiliser plsrs fois méthode
    public:
        bool isEmpty()const;
        friend class controler;
        friend class river;
    };
}
//opstream inutile?? on ne va pas afficher la pioche
// iterator déjà inclu dans vector; memento??
#endif //PROJETLO21A25_PILE_H