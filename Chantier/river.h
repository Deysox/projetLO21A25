#ifndef PROJETLO21A25_RIVER_H
#define PROJETLO21A25_RIVER_H
#include <vector>
#include <iostream>
#include "../Tuiles/tile.h"
#include "pile.h"
using namespace std;
using namespace Barnabe;
namespace Amalena {
    /*
     *Rivière du jeu
     */
    class River{
        vector<Tile*> tiles;
        int max_tiles;
        Pile& pile;
        /*
         *Méthode interne permettant de remplir la rivière à partir du deck
         */
        void fillriver();
    public:
        /*
         *Donne la tuile en fonction de la position indiquée
         * @param position de type size_t
         * @return Tile&
         */
        Tile& giveTile(size_t position);
        /*
         *Indique s'il ne reste qu'une tuile dans la rivière ( et donc le moment de la remplir
         *@return un booleen si vrai il ne reste qu'une tuile
         */
        bool stay1()const;
        /*
         *donne la position d'une tuile passée en paramètre
         * @param t :  pointeur sur une tuile
         * @return size_t la position
         */
        size_t getPosition(const Tile* t) const;
        /*
         *constructeur
         *@param nb le nombre de tuiles max dans la rivière (relatif au nombre de joueur)
         */
        River(size_t nb, Pile& pile);
        /*
         *constructeur pour la sauvegarde
         * prenant en plus en paramètre un vecteur des tuiles présents dans la rivière
         */

        River(vector<Tile*>& tiles, size_t nb, Pile& pile): tiles(tiles), max_tiles(nb), pile(pile){};
        /*
         *destructeur
         */
        ~River();
        /*
         * constructeur par recopie
         */
        River(const River& r):tiles(r.tiles), max_tiles(r.max_tiles), pile(r.pile){};
        /*
         *opératuer d'affectation
         */
        River& operator=(const River& f);
        /*
         *transcription en chaine pour la sauvegarde
         */
        string toString() const;
        /*
         *renvoi la taille actuelle de la rivière
         *@return taille de la rivière
         */
        size_t getSize() const {
            return tiles.size();
        }
        /*
         *getter
         */
        const vector<Tile*>& getTiles() const { return tiles; }
        void addTilesInRiver(Tile* tile) {
            tiles.push_back(tile);
        }
        void clearVectorRiver() {
            tiles.clear();
        }
    private:
        class RiverIterator {
            std::vector<Tile*>::iterator current;
            friend class River;
            RiverIterator(const std::vector<Tile*>::iterator& it)
                : current(it) {}
        public:
            // ++prefixe
            RiverIterator& operator++() {
                ++current;
                return *this;
            }

            RiverIterator& operator--() {
                --current;
                return *this;
            }

            bool operator!=(const RiverIterator& other) const {
                return current != other.current;
            }

            Tile& operator*() {
                return **current;
            }
        };

    public:
        RiverIterator begin() {
            return RiverIterator(tiles.begin());
        }

        RiverIterator end() {
            return RiverIterator(tiles.end());
        }


    };
    /*
    *surcharde de l'opérateur << pour l'affichage en mode console
    */
    ostream& operator<<(ostream& f, Amalena::River& r);
}
#endif //PROJETLO21A25_RIVER_H