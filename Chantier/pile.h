

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
    /**
     *Au départ identique au deck puis mise à jour
     *au fur et à mesure du remplissage de la rivière
     */

    class Pile{
        /**
         * Vecteur de pointeur des tuiles disponible dans la pioche
         */
        vector <Barnabe::Tile*> tiles;
        /**
         * reférence au deck associé à la pioche
         */
        Eloise::Deck& deck;
        /**
         * constructeur par recopie
         * @param p pile à recopier
         */
        Pile(const Pile& p):deck(p.deck), tiles(p.tiles){};
        friend class river;
    public:

        /**
         *Constructeur, les pointeur sont initialement randomisés
         */
        explicit Pile(Eloise::Deck& d);
        /**
         *constructeur pour la sauvegarde
         *@param reference au deck associé
         *@param vecteur de pointeur des tuiles présentes dans la pioche dans la sauvegarde
         */
        explicit Pile(Eloise::Deck& d,vector <Barnabe::Tile*>& t): deck(d),tiles(t){};
        /**
        *opérateur d'affectation
         */

        Pile& operator=(const Pile& p);
        /**
         *@return booleen indiquant si la pile est vide
         */
        bool isEmpty() const;
        /**
         *Fonction de distribution
         *@return un pointeur sur une tuile (donne une tuile est retire le pointeur du vecteur)
         */
        Barnabe::Tile* Draw();
        /**
         *destructeur par défaut
         */
        ~Pile()=default;

        /**
         *
         * @param tile pointeur vers une tuile à ajouter à la fin de la pile
         */
        void addTilesInPile(Barnabe::Tile* tile) {
            tiles.push_back(tile);
        }

        /**
         *Moyen de nettoyer le vecteur
         */
        void clearVectorPile() {
            tiles.clear();
        }
    private:
        /**
         *Iterateur repris à partir de l'itérateur sur notre vecteur
         *
         */
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