

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
    /*Au départ identique au deck puis mis à jours au fur et à mesure du remplissage de la rivière
     */

    class Pile{
        vector <Barnabe::Tile*> tiles;
        Eloise::Deck& deck;
        Pile(const Pile& p):deck(p.deck), tiles(p.tiles){};
        friend class river;
    public:

        /*
         *Constructeur, de la classe pile initialement avec pointe vers toutes les tuiles du deck indiqué (de facon aléatoire)
         */
        explicit Pile(Eloise::Deck& d);


        /*
         *constructeur pour la sauvegarde
         */

        explicit Pile(Eloise::Deck& d,vector <Barnabe::Tile*>& t): deck(d),tiles(t){};
        /*
        *opérateur d'affectation
         */

        Pile& operator=(const Pile& p);
        /*
         *Méthode renvoyant si la pile est vide
         */
        bool isEmpty() const;
        /*
         *Fonction de distribution
         *@return un pointeur sur une tuile (donne une tuile est retire le pointeur du vecteur
         */
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