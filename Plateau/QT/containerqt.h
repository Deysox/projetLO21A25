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

    template <typename Container_Type, typename Item>
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
        Container_Type cells;

        /**
         * Objet à afficher.
         * Peut être un plateau, une tuile...
         */
        const Item* item;
    public:
        /**
         * Constructeur de la classe ContainerQt
         * @param parent Widget parent du conteneur
         * @param s Taille des cases en pixels
         */
        explicit ContainerQt(QWidget* parent, const Item* i, int s = 40) : QWidget(parent), item(i), size(s) {}

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
         * Accesseur en lecture sur l'objet à afficher.
         * @return Pointeur vers l'objet à afficher
         */
        virtual const Item* getItem() const {return item;}
        /**
         * Accesseur en écriture sur l'objet à afficher.
         * @param it Objet à afficher
         */
        virtual void setItem(const Item* it) {item = it;}

    protected:
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
