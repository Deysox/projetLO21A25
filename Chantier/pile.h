

#ifndef PROJETLO21A25_PILE_H
#define PROJETLO21A25_PILE_H
#include <vector>
#include <string>

#include "deck.h"
#include "tile.h"


class river;
using namespace std;



namespace Amalena {

    class Pile{
        vector <Barnabe::Tile*> tiles;
        Eloise::Deck& deck;
        Pile(const Pile& p):deck(p.deck), tiles(p.tiles){}; //et si retour en arrière?
        //piocher  ?? creéer une facon dans piocher plusieurs ou utiliser plsrs fois méthode
        friend class river;
    public:
        //initialisation à voir comment est constitué le deck en type de donné pour créer tiles
        explicit Pile(Eloise::Deck& d); //gérer aléatoire à faire
        //après sauvegarde
        explicit Pile(Eloise::Deck& d,vector <Barnabe::Tile*>& t): deck(d),tiles(t){};
        bool isEmpty() const;//création d'un getters pour état
        Barnabe::Tile* Draw();
        ~Pile();
        Pile& operator=(const Pile& f);
    };
}

#endif //PROJETLO21A25_PILE_H