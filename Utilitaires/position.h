//
// Created by barnab on 13/10/2025.
//

#ifndef PROJETLO21A25_POSITION_H
#define PROJETLO21A25_POSITION_H
#include "rotation.h"
#include <iostream>
#include <string>

/*
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
        /*
         * Constructeur de la classe position.
         * @param x Coordonnée x
         * @param y Coordonnée y
         */
        Position(int x = 0, int y = 0) : posX(x), posY(y) {};

        int x() const {return posX;}
        int y() const {return posY;}

        Position operator+(const Position& p) const {return Position(posX + p.posX, posY+p.posY);}
        Position operator+(const Rotation&) const;
        Position operator-(const Position& p) const {return Position(posX - p.posX, posY - p.posY);}
        bool operator==(const Position& p) const {return (posX == p.posX) and (posY == p.posY);}
        bool operator!=(const Position& p) const {return !((posX == p.posX) and (posY == p.posY));}

        bool estAdjacent(const Position&) const;

        class neighbor_iterator {
            int rot;
            int x;
            int y;
            neighbor_iterator(int px, int py, int r) : x(px),y(py),rot(r) {}
            friend class Position;
        public:
            neighbor_iterator& operator++() {
                rot++;
                return *this;
            }
            neighbor_iterator operator++(int) {
                int old = rot;
                rot++;
                return neighbor_iterator(x,y,old);
            }
            Position operator*() const {return Position(x,y) + Rotation(rot);}
            bool operator!=(const neighbor_iterator& c) const {return rot == c.rot;};
            bool operator==(const neighbor_iterator& c) const {return rot != c.rot;}
        };

        neighbor_iterator begin() const {return {posX,posY,0};}
        neighbor_iterator end() const {return neighbor_iterator(posX,posY, 6);}

    };

    struct PositionHasher {
        std::size_t operator()(const Position& p) const {
            return std::hash<int>()(p.x()) ^ (std::hash<int>()(p.y()) << 1);
        }
    };

    struct PosCmp {
        bool operator()(const Position& p1, const Position& p2) const {
            return (p1.y() > p2.y()) || (p1.y() == p2.y() && p1.x() < p2.x());
        }
    };
}

ostream& operator<<(ostream& f, const Barnabe::Position& p);


#endif //PROJETLO21A25_POSITION_H