//
// Created by barnab on 17/12/2025.
//

#ifndef AKROPOLIS_TILEQT_H
#define AKROPOLIS_TILEQT_H

#include "cellqt.h"
#include "containerqt.h"
#include "../../Tuiles/tile.h"

namespace Barnabe {
    /**
     * Représentation graphique d'une tuile du jeu Akropolis.
     * Version abstraite d'une tuile pour permettre les déclinaisons d'affichage simples.
     */
    class TileQt : public ContainerQt {
    protected:
        /**
         * Vecteur comportant des pointeurs vers les différents affichages de cases.
         */
        vector<CellQtFull*> cells;
        /**
         * Tuile à représenter
         */
        const Tile* tile;
    public:
        /**
         * Constructeur de la classe TileQt
         * @param parent Widget parent
         * @param t Tuile à représenter
         * @param s Taille des cases (rayon)
         */
        TileQt(QWidget* parent, const Tile* t, int s = 40) : ContainerQt(parent, s), tile(t) {
            setStyleSheet("background-color: rgba(0,0,0,0)");
        }

        /**
         * Vide la case en désallouant les CellQt et en vidant le vecteur
         */
        void empty() override {
            for (const CellQtFull* vec : cells) delete vec;
            cells.clear();
        }

    };

    /**
     * Représentation graphique d'une tuile classique du jeu Akropolis.
     */
    class ClassicTileQt : public TileQt {
    public:
        /**
         * Constructeur de ClassicTileQt
         * @param parent Widget parent
         * @param ct Tuile à afficher
         * @param s Taille des cases (rayon)
         */
        ClassicTileQt(QWidget* parent, const ClassicTile* ct, int s = 40) : TileQt(parent, ct, s) {
            setFixedSize(7*size/2,2*std::sqrt(3)*size);
            updateDisplay();
        }

        /**
         * Accesseur en écriture de la tuile à afficher
         * @param ct Tuile à afficher
         */
        void setTile(const ClassicTile *ct) {tile = ct;}
        /**
         * Accesseur en lecture de la tuile à afficher
         * @return Pointeur vers Tile
         */
        const Tile* getTile() const {return tile;}

        /**
         * Construction de l'affichage de la tuile.
         */
        void draw() override;
    };


}

#endif //AKROPOLIS_TILEQT_H