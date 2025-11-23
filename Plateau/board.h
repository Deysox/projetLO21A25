#ifndef PROJETLO21A25_PLATEAU_H
#define PROJETLO21A25_PLATEAU_H

#include <map>
#include <vector>
#include <string>
#include <unordered_map>

#include "../Tuiles/cell.h"
#include "../Tuiles/tile.h"

#include "../Utilitaires/position.h"
#include "../Utilitaires/rotation.h"
using namespace std;

namespace Barnabe {
    //using namespace Marilou;

    /*
     * Modélise un plateau de joueur du jeu Akropolis.
     * Le contenu du plateau est modélisé par des pointeurs const vers des cases Cell. Les cases sont indexées
     * par leurs positions dans la grille hexagonale, modélisés par des objets Position.
     * La hauteur d'une case dans le plateau est un unsigned int. Une hauteur de 0 correspond à l'absence de case.
     *
     * La classe Board n'effectue pas de vérification sur la validité des coups joués, et ne permet que la gestion
     * par case, et non par tuile. Elle est destinée à être utilisée avec un objet BoardManager pour effectuer une
     * interface.
     *
     * L'implémentation se fait à l'aide d'une std::unordered_map de clés Position et de valeurs
     * std::pair<const Cell*, unsigned int>
     */
    class Board {
        unordered_map<Position, pair<const Cell*, unsigned int>, PositionHasher> cells;
        Position corner_tl;
        Position corner_br;
    public:
        class iterator;
        iterator begin() const;
        iterator end() const;

        /*
         * Constructeur de la classe Board. Par défaut, le plateau est vide.
         */
        Board();

        /*
         * Destructeur de la classe Board.
         */
        ~Board();

        /*
         * Constructeur par recopie de la classe Board.
         * @param b Board à recopier
         */
        Board(const Board& b);

        /*
         * Opérateur d'affectation de la classe Board.
         * @param b Board à recopier
         */
        Board& operator=(const Board&);

        /*
         * Accesseur en lecture de la case de position pos dans le Board.
         * @param pos Position de la case
         * @return Pointeur const sur la case de coordonnées pos. nullptr si aucune case à l'emplacement indiqué.
         */
        const Cell* getCell(Position pos) const;

        /*
         * Accesseur en lecture de la case de position pos dans le Board.
         * @param x Coordonnée x de la case
         * @param y Coordonnée y de la case
         * @return Pointeur const sur la case de coordonnées x et y. nullptr si aucune case à l'emplacement indiqué.
         */
        const Cell* getCell(int x, int y) const;

        /*
         * Accesseur en lecture sur la hauteur de la case de position pos dans le Board.
         * @param pos Position de la case
         * @return unsigned int représentant la hauteur de la case de coordonnées pos.
         * nullptr si aucune case à l'emplacement indiqué.
         */
        unsigned int getHeight(Position pos) const;
        /*
         * Accesseur en lecture sur la hauteur de la case de position pos dans le Board.
         * @param x Coordonnée x de la case
         * @param y Coordonnée y de la case
         * @return unsigned int représentant la hauteur de la case de coordonnées x et y.
         * nullptr si aucune case à l'emplacement indiqué.
         */
        unsigned int getHeight(int x, int y) const;

        //Position findCell(const Cell&) const;

        /*
         * Accesseur en écriture de la case de position pos. Assigne l'emplacement pos à la case c et à la hauteur h.
         * @param pos Position de l'emplacement à écrire
         * @param h Hauteur à écrire
         * @param c Pointeur const vers la case à écrire
         */
        void setCell(Position pos, unsigned int h, const Cell* c);

        /*
         * Accesseur en écriture de la case d'emplacement x et y.
         * Assigne l'emplacement de coordonnées x et y à la case c et à la hauteur h.
         * @param x Coordonnée x de l'emplacement à écrire
         * @param y Coordonnée y de l'emplacement à écrire
         * @param h Hauteur à écrire
         * @param c Pointeur const vers la case à écrire
         */
        void setCell(int x, int y, unsigned int h, const Cell* c);


        //void validPos(const vector<Position>&) const;

        /*
         * Accesseur en lecture des coins du plateau.
         * Les coins ne sont pas nécessairement des cases du plateau, mais plutôt des positions.
         * @return pair contenant le coin supérieur gauche et le coin inférieur droit, dans cet ordre.
         *
         *
         */
        std::pair<Position, Position> getCorners() const;

        friend ostream& operator<<(ostream& f, const Board& p);

    };
    string lenStringInt(int x);
    ostream& operator<<(ostream& f, const Board& p);

}


#endif //PROJETLO21A25_PLATEAU_H