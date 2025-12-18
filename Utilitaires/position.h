//
// Created by barnab on 13/10/2025.
//

#ifndef PROJETLO21A25_POSITION_H
#define PROJETLO21A25_POSITION_H
#include "rotation.h"
#include <iostream>
#include <string>

using std::string, std::ostream;

/**
 * Représente la position d'une case dans un plateau d'Akropolis.
 * Les coordonnées des positions sont des entiers relatifs. La position (0;0) correspond à l'origine du repère.
 * Pour une position (x;y) donnée, les cases voisines sont déterminées de la manière suivante :
 * - Si x est pair, les voisins sont (x;y+1), (x+1;y+1), (x+1;y), (x;y-1), (x-1;y), (x-1;y+1)
 * - Si x est impair, les voisins sont (x;y+1), (x+1;y), (x+1;y-1), (x;y-1), (x-1;y-1), (x-1;y)
 * Supporte les calculs arithmétiques basiques sur des vecteurs à deux coordonnées.
 *
 */
namespace Barnabe {
    class Position {
        int posX;
        int posY;
    public:
        /**
         * Constructeur de la classe position.
         * @param x Coordonnée x
         * @param y Coordonnée y
         */
        explicit Position(int x = 0, int y = 0) : posX(x), posY(y) {}
        Position(const Position& p) : posX(p.x()), posY(p.y()) {}

        /**
         * Accesseur en lecture pour la coordonnée x
         * @return Coordonée x
         */
        [[nodiscard]] int x() const {return posX;}

        /**
         * Accesseur en lecture pour la coordonnée y
         * @return Coordonnée y
         */
        [[nodiscard]] int y() const {return posY;}

        /**
         * Addition de deux positions terme à terme.
         * z = t + p
         * (x,y) = (xt+xp,yt+yp)
         * @param p Second opérande
         * @return Position résultat du calcul
         */
        Position operator+(const Position& p) const {return Position(posX + p.posX, posY+p.posY);}

        /**
         * Addition d'une position et d'une rotation.
         * Renvoie une Position correspondant à la case adjacente à l'objet dans la direction
         * indiquée par la rotation r
         * @param r Rotation indiquant la direction
         * @return Position résultat du calcul
         */
        Position operator+(const Rotation& r) const;

        /**
         * Soustraction
         * z = t - p
         * (x,y) = (xt-xp,yt-yp)
         * @param p Second opérande
         * @return Position résultat du calcul
         */
        Position operator-(const Position& p) const {return Position(posX - p.posX, posY - p.posY);}

        /**
         * Comparateur de positions.
         * @param p Position à comparer
         * @return true si les coordonnées x et y sont égales deux à deux
         */
        bool operator==(const Position& p) const {return (posX == p.posX) and (posY == p.posY);}

        /**
         * Comparateur de positions.
         * @param p Position à comparer
         * @return false si les coordonnées x et y sont égales deux à deux
         */
        bool operator!=(const Position& p) const {return !((posX == p.posX) and (posY == p.posY));}

        /**
         * Teste si une case fournie en paramètre est adjacente.
         * @param p Position à comparer
         * @return true si les deux positions sont adjacentes
         */
        [[nodiscard]] bool isNeighbour(const Position& p) const;

        /**
         * Itérateur sur les positions voisines d'une case donnée.
         * L'opérateur * renvoie un objet de type Position.
         * Le parcours s'effectue dans le sens horaire, dans le sens des aiguilles d'une montre à partir
         * de la rotation 0 (case (x;y+1)).
         */
        class iterator {
            int rot;
            int x;
            int y;
            iterator(int px, int py, int r) : x(px),y(py),rot(r) {}
            friend class Position;
        public:
            iterator& operator++() {
                rot++;
                return *this;
            }
            iterator operator++(int) {
                int old = rot;
                rot++;
                return {x,y,old};
            }
            Position operator*() const {return Position(x,y) + Rotation(rot);}
            bool operator!=(const iterator& c) const {return rot != c.rot;};
            bool operator==(const iterator& c) const {return rot == c.rot;}
        };



        /**
         * Itérateur de début de parcours
         * @return neighbor_iterator sur la case (x;y+1)
         */
        [[nodiscard]] iterator begin() const {return {posX,posY,0};}
        /**
         * Itérateur de fin de parcours
         * @return neighbor_iterator correspondant à la fin du parcours
         */
        [[nodiscard]] iterator end() const {return {posX,posY, 6};}
        /**
         * Itérateur de début de parcours
         * @return neighbor_iterator sur la case (x;y+1)
         */
        [[nodiscard]] iterator cbegin() const {return {posX,posY,0};}
        /**
         * Itérateur de fin de parcours
         * @return neighbor_iterator correspondant à la fin du parcours
         */
        [[nodiscard]] iterator cend() const {return {posX,posY, 6};}

        /**
         * @return Chaîne de caractères sous la forme (x;y)
         */
        [[nodiscard]] string toString() const {return "("+std::to_string(x())+";"+std::to_string(y())+")";}

    };

    /**
     * Fonction de hachage pour stocker des données dans une unordered_map<Position, T>
     */
    struct PositionHasher {
        std::size_t operator()(const Position& p) const {
            return std::hash<int>()(p.x()) ^ (std::hash<int>()(p.y()) << 1); // Fonction de hachage pour fournir
            // un identifiant unique à chaque Position dans la unordered_map
        }
    };

    /**
     *
     * @param f Flux de sortie
     * @param p Position
     * @return Flux modifié
     */
    ostream& operator<<(ostream& f, const Position& p);
}




#endif //PROJETLO21A25_POSITION_H