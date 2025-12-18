//
// Created by barnab on 13/10/2025.
//

#ifndef PROJETLO21A25_ROTATION_H
#define PROJETLO21A25_ROTATION_H

namespace Barnabe {

    /**
     * Représente la rotation d'une case hexagonale ou d'une tuile dans le jeu Akropolis.
     * La rotation peut prendre six valeurs possibles, modélisé par un entier r allant de 0 à 5.
     * L'objet Rotation correspond à r Rotations successives de 60° dans le sens horaire
     * à partir de la position initiale.
     *
     * Pour les cases individuelles non bicolores, la rotation n'a aucun impact.
     * Pour les cases individuelles bicolores, la rotation influe sur les relations de connexion entre couleurs sur
     * le plateau. La moitié des voisins seront considérés comme adjacents à une tuile monochrome de la première couleur,
     * tandis que l'autre moitié le sera avec la seconde.
     *
     * Pour les tuiles à trois cases, la rotation se présente comme suit.
     * /A_\
     * \__//B_\
     * /PP\\__/
     * \PP/
     * La rotation s'effectue dans le sens horaire, autour de la tuile pivot marquée P. Une Rotation 1 sur cette tuile
     * donnerait alors :
     *
     *     /A_\
     * /PP\\__/
     * \PP//B_\
     *     \__/
     */
    class Rotation {
        int r;
    public:
        /**
         * Constructeur de la classe Rotation.
         * @param rot Valeur initiale de la rotation
         */
        Rotation(int rot = 0) : r(rot%6) {}  // Conversion implicite possible

        /**
         * Accesseur en lecture de l'attribut r
         * @return Entier correspondant à la rotation, entre 1 et 6
         */
        int value() const {return r;}

        /**
         * Additionne deux rotations
         * @param Second opérande
         * @return Objet Rotation correspondant à la rotation totale effectuée par cumul des rotations
         * entraînées par les opérandes.
         */
        Rotation operator+(const Rotation& other) const {return {(r+other.r)%6};};

        /**
         * Soustrait deux rotations
         * @param Second opérande
         * @return Objet Rotation correspondant à la rotation totale effectuée par cumul des rotations
         * entraînées dans le sens horaire pour le premièr opérande
         * et dans le sens inverse pour le second opérande.
         */
        Rotation operator-(const Rotation&) const {return {(r-1)%6};}

        /**
         * Incrémente la rotation d'un sixième de tour
         * @return Rotation modifiée
         */
        Rotation& operator++() {r++; return *this;}
        /**
         * Incrémente la rotation d'un sixième de tour
         * @return Rotation non modifiée
         */
        Rotation operator++(int) {int old = r; r++; return {old};};
        /**
         * Compare deux rotations
         * @param other Second opérande
         * @return True si les deux rotations ont la même valeur
         */
        bool operator==(const Rotation& other) const {return r == other.r;};
        /**
         * Compare deux rotations
         * @param other Second opérande
         * @return False si les deux rotations ont la même valeur
         */
        bool operator!=(const Rotation& other) const {return r != other.r;}
    };
}


#endif //PROJETLO21A25_ROTATION_H