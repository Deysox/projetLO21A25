

#ifndef PROJETLO21A25_PILE_H
#define PROJETLO21A25_PILE_H
#include <vector>
#include <string>

#include "../Tuiles/deck.h"
#include "../Tuiles/tile.h"


class river;
using namespace std;

using namespace Barnabe;

namespace Amalena {

    class Pile{
        vector <Barnabe::Tile*> tiles;
        Eloise::Deck& deck;
        Pile(const Pile& p):deck(p.deck), tiles(p.tiles){}; //et si retour en arrière?
        //piocher  ?? creéer une facon dans piocher plusieurs ou utiliser plsrs fois méthode
        friend class river;
    public:
        Pile& operator=(const Pile& p);
        //initialisation à voir comment est constitué le deck en type de donné pour créer tiles
        explicit Pile(Eloise::Deck& d); //gérer aléatoire à faire
        //après sauvegarde
        explicit Pile(Eloise::Deck& d,vector <Barnabe::Tile*>& t): deck(d),tiles(t){};
        bool isEmpty() const;//création d'un getters pour état
        Barnabe::Tile* Draw();
        ~Pile();
        void addTilesInPile(Barnabe::Tile* tile) {
            tiles.push_back(tile);
        }
        void clearVectorPile() {
            tiles.clear();
        }
    private:
        class PileIterator {
            std::vector<Tile*>::iterator current;
            friend class Pile;
            PileIterator(const std::vector<Tile*>::iterator& it)
                : current(it) {}
        public:
            // ++prefixe
            PileIterator& operator++() {
                ++current;
                return *this;
            }

            PileIterator& operator--() {
                --current;
                return *this;
            }

            bool operator!=(const PileIterator& other) const {
                return current != other.current;
            }

            Tile& operator*() {
                return **current;
            }
        };

    public:
        PileIterator begin() {
            return PileIterator(tiles.begin());
        }

        PileIterator end() {
            return PileIterator(tiles.end());
        }
    };
}

#endif //PROJETLO21A25_PILE_H