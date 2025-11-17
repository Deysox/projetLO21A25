//
// Created by barnab on 05/10/2025.
//

#ifndef PROJETLO21A25_PILE_H
#define PROJETLO21A25_PILE_H
#include <vector>
#include <string>
class river;
using namespace std;
//using namespace Marilou;
namespace Marilou {//temporaire
    class Tile;
}
namespace Amalena {

    class Pile{
        vector <Marilou::Tile*> tiles;
        Pile(const Pile& p)=delete;//et si retour en arrière?
        Pile& operator=(Pile& p)=delete;//? utilisation si memo retour arrière
        //piocher  ?? creéer une facon dans piocher plusieurs ou utiliser plsrs fois méthode
        friend class river;
    public:
        explicit Pile(vector <Marilou::Tile*> t): tiles(t){};
        bool isEmpty() const;//création d'un getters pour état
        Marilou::Tile* Draw();
        ~Pile();
    };
}
//opstream inutile?? on ne va pas afficher la pioche
#endif //PROJETLO21A25_PILE_H