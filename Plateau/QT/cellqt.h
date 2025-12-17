//
// Created by barnab on 16/12/2025.
//

#ifndef AKROPOLIS_CELLQT_H
#define AKROPOLIS_CELLQT_H



#include "../../Utilitaires/position.h"
#include "../../Tuiles/cell.h"

#include <QWidget>
#include <QMainWindow>
#include <QMouseEvent>

#include <QLabel>
#include <QBrush>
#include <QPen>
#include <QPainter>

namespace Barnabe {
    /**
     * Classe abstraide représentant un widget affichant une case du jeu Akropolis.
     * Définit une interface pour les différents types de cases.
     */
    class CellQt : public QWidget {
    protected:
        /**
         * Taille de la case en pixels (rayon)
         */
        int size;
        /**
         * Largeur réelle du widget
         * w = 2*size
         */
        int w;
        /**
         * Hauteur réelle du widget
         * h = sqrt(3)*size
         */
        int h;

        /**
         * Position dans un plateau représentée par la case dans son conteneur
         */
        Position pos;

        /**
         * Bloque ou non l'effet lors du passage de la souris
         */
        bool locked;

    public:
        /**
         * Constructeur de la classe CellQt
         * @param parent Widget parent
         * @param p Position dans un plateau repésentée par la case
         * @param l Verrouillage par défaut
         * @param s Taille de la case
         */
        CellQt(QWidget* parent, Position p, bool l = false, int s = 40);

        /**
         * Destructeur de CellQt
         */
        virtual ~CellQt() = default;

        /**
         * Dessine la case sous la forme d'un hexagone.
         * @param event QPaintEvent
         */
        void paintEvent(QPaintEvent *event) override;

        /**
         * Calcule le remplissage du dessin de la case.
         * En fonction du type de case, le remplissage diffère, en devant possiblement s'adapter à la couleur,
         * au type...
         * @return QBrush utilisée pour le remplissage du tracé
         */
        virtual const QBrush brush() const = 0;
        /**
         * Calcule le contour du dessin de la case.
         * En fonction du type de case, le contour diffère, en devant possiblement s'adapter à la couleur,
         * au type...
         * @return QPen utilisée pour le contour du tracé
         */
        virtual const QPen pen() const = 0;

        /**
         * Actions à effectuer après le traçage de la case.
         */
        virtual void endPaintEventActions() = 0;

        /**
         * Verrouille la case
         */
        void lock() {locked = true;}
        /**
         * Déverrouille la case
         */
        void unlock() {locked = false;}



    };

    /**
     * Affiche le contenu d'une case d'un plateau, avec sa couleur, son type et sa hauteur.
     * Hérite de CellQt, permettant un affichage sous forme d'hexagone.
     * Au survol, un QToolTip affiche les informations de la case.
     */
    class CellQtFull : public CellQt {
        /**
         * Map utilisée pour la génération du QPen et de la QBrush
         */
        static map<Color, pair<QColor, QColor>> colors;
        /**
         * Map utilisée pour la génération du tooltip
         */
        static map<Color, string> colorText;
        /**
         * Map utilisée pour la génération du tooltip
         */
        static map<Color, string> placeText;
        /**
         * Couleur de la case
         */
        Color color;
        /**
         * Type de la case
         */
        Type type;
        /**
         * Hauteur de la case
         */
        unsigned int height;
        /**
         * Label affichant la hauteur de la case
         */
        QLabel* label;
    public:
        /**
         * Constructeur de la case CellQtFull
         * @param parent Widget parent
         * @param p Position décrite
         * @param l Verrouillage par défaut
         * @param s Taille de la case (rayon)
         * @param c Couleur
         * @param t Type
         * @param hght Hauteur
         */
        CellQtFull(QWidget* parent, Position p, bool l = false, int s = 40, Color c = Color::BLUE, Type t = Type::DISTRICT, unsigned int hght = 0);

        /**
         * Remplissage de la case. Renvoie un remplissage plein de la couleur de la case.
         * Utilise la variante sombre en cas de type Place.
         * @return QBrush
         */
        const QBrush brush() const override;
        /**
         * Contour de la case. Renvoie un contour de la variante sombre de la couleur de la case.
         * Utilise la variante claire en cas de type Place.
         * @return QPen
         */
        const QPen pen() const override;

        /**
         * Gère la coloration du label en cas de survol par la souris
         */
        void endPaintEventActions() override;

    };

    /**
     * Affiche une case inexistante utilisée pour dessiner les contours du plateau et transmettre à l'utilisateur les
     * emplacement adjacents.
     */
    class CellQtEmpty : public CellQt {
    public:
        /**
         * Constructeur de CellQtEmpty
         * @param parent Widget parent
         * @param p Position décrite
         * @param l Verrouillage initial
         * @param s Taille de la case (rayon)
         */
        CellQtEmpty(QWidget* parent, Position p, bool l = false, int s = 40);

        /**
         * Remplissage en pointillés gris.
         * @return QBrush
         */
        const QBrush brush() const override;

        /**
         * Contour invisible
         * @return QPen
         */
        const QPen pen() const override;

        /**
         * Aucune action post-traçage.
         */
        void endPaintEventActions() override {}
    };
}

#endif //AKROPOLIS_CELLQT_H