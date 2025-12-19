//
// Created by barnab on 17/12/2025.
//

#ifndef AKROPOLIS_TILEQT_H
#define AKROPOLIS_TILEQT_H

#include "cellqt.h"
#include "containerqt.h"
#include "tile.h"

namespace Barnabe {
    /**
     * Représentation graphique d'une tuile du jeu Akropolis.
     * Version abstraite d'une tuile pour permettre les déclinaisons d'affichage simples.
     */
    class TileQt : public ContainerQt<vector<CellQtFull*>,Tile> {
    public:
        /**
         * Constructeur de la classe TileQt
         * @param parent Widget parent
         * @param t Tuile à représenter
         * @param s Taille des cases (rayon)
         */
        TileQt(QWidget* parent, const Tile* t, int s = 40) : ContainerQt(parent, t, s) {
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
         * Accesseur en écriture pour la ClassicTile à afficher
         * Tente de convertir t en const ClassicTile*. Si impossible, lève une exception
         * @param t ClassicTile à utiliser comme objet à afficher
         */
        void setItem(const Tile* t) override {
            const ClassicTile* ptr = dynamic_cast<const ClassicTile *>(t);
            if (ptr) item = ptr;
            else throw TileException("Impossible to cast to ClassicTile");
        }

        /**
         * Accesseur en écriture pour la ClassicTile à afficher
         * @param t ClassicTile à utiliser comme objet à afficher
         */
        void setItem(const ClassicTile* t) {item = t;}

        /**
         * Construction de l'affichage de la tuile.
         */
        void draw() override;
    };


}

#endif //AKROPOLIS_TILEQT_H