//
// Created by barnab on 17/12/2025.
//

#ifndef AKROPOLIS_CONTAINER_H
#define AKROPOLIS_CONTAINER_H
#include <QWidget>

namespace Barnabe {
    /**
     * Classe abstraite définissant une interface pour les widgets contenant des cellules, en particulier
     * TileQt et BoardQt.
     *
     * Hérite de QWidget
     *
     * Gère le cycle de vie des CellQt
     */

    template <typename T>
    class ContainerQt : public QWidget {
    protected:
        /**
         * Taille des cases à afficher en pixels.
         */
        int size;

        /**
         * Conteneur des widgets QT.
         * Peut être un array, un vecteur, une map...
         */
        T cells;
    public:
        /**
         * Constructeur de la classe ContainerQt
         * @param parent Widget parent du conteneur
         * @param s Taille des cases en pixels
         */
        explicit ContainerQt(QWidget* parent, int s = 40) : QWidget(parent), size(s) {}

        /**
         * Suppression du constructeur par recopie
         */
        ContainerQt(const ContainerQt&) = delete;
        /**
         * Suppression de l'opérateur d'affecation
         */
        ContainerQt& operator=(const ContainerQt&) = delete;

        /**
         * Actualisation de l'affichage du conteneur.
         * Effectue dans l'ordre :
         * - Désallocation et nettoyage des widgets enfants
         * - Création des widgets pour l'affichage
         * - Actualisation de l'affichage grâce à la méthode update() de Qt
         */
        void updateDisplay() {empty(); draw(); update();}

        /**
         * Comportement à adopter pour générer l'affichage
         */
        virtual void draw() = 0;

        /**
         * Comportement à adopter pour vider le contenu du conteneur
         */
        virtual void empty() = 0;

    };
}

#endif //AKROPOLIS_CONTAINER_H
