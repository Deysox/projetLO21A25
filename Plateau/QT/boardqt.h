//
// Created by barnab on 13/12/2025.
//

#ifndef PROJETLO21A25_HEXAGON_H
#define PROJETLO21A25_HEXAGON_H

#include "../../Plateau/board.h"
#include "cellqt.h"
#include "containerqt.h"


namespace Barnabe {
    /**
     * Représentation graphique d'un plateau du jeu Akropolis sous forme de Widget QT.
     */
    class BoardQt : public ContainerQt<unordered_map<Position, CellQt*, PositionHasher>,Board> {
    public:
        /**
         * Constructeur de la classe BoardQt
         * @param parent Widget parent
         * @param b Plateau à représenter
         * @param s Taille des cases (rayon)
         */
        BoardQt(QWidget* parent, const Board* b, int s = 40) : ContainerQt(parent,b,s) {updateDisplay();}

        /**
         * Désalloue les CellQt en itérant sur la map
         */
        void empty() override;

        /**
         * Création de l'affichage
         */
        void draw() override;

        /**
         * Verrouille toutes les cases du plateau
         */
        void lock() {for (const pair<Position, CellQt*> p : cells) p.second->lock();}
        /**
         * Déverrouille toutes les cases du plateau
         */
        void unlock() {for (const pair<Position, CellQt*> p : cells) p.second->unlock();}
    };
}

#endif //PROJETLO21A25_HEXAGON_H