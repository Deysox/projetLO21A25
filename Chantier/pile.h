

#ifndef PROJETLO21A25_PILE_H
#define PROJETLO21A25_PILE_H
#include <vector>
#include <string>
#include "Deck.h"
class river;
using namespace std;


namespace Amalena {

    class Pile{
        vector <Barnabe::ClassicTile*> tiles;
        Deck& deck;
        Pile(const Pile& p):deck(p.deck), tiles(p.tiles){}; //et si retour en arrière?
        Pile& operator=(Pile& p)=delete;//? utilisation si memo retour arrière
        //piocher  ?? creéer une facon dans piocher plusieurs ou utiliser plsrs fois méthode
        friend class river;
    public:
        //initialisation à voir comment est constitué le deck en type de donné pour créer tiles
        explicit Pile(Deck& d); //gérer aléatoire à faire
        //après sauvegarde
        explicit Pile(Deck& d,vector <Barnabe::ClassicTile*>& t): deck(d),tiles(t){};
        bool isEmpty() const;//création d'un getters pour état
        Barnabe::ClassicTile* Draw();
        ~Pile();
    };
}

#endif //PROJETLO21A25_PILE_H