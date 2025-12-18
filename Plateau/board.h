#ifndef PROJETLO21A25_PLATEAU_H
#define PROJETLO21A25_PLATEAU_H

#include <map>
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "cell.h"
#include "position.h"

using json = nlohmann::json;
using std::map, std::unordered_map, std::pair;

namespace Barnabe {
    /**
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
        /**
         * Map statique utilisée pour le chargement d'une sauvegarde à partir d'un fichier JSON
         */
        static map<string, Color> stringToColor;
        /**
         * Map statique utilisée pour le chargement d'une sauvegarde à partir d'un fichier JSON
         */
        static map<string, Type> stringToType;
        /**
         * Map statique utilisée pour l'enregistrement d'une sauvegarde vers un fichier JSON
         */
        static map<Color, string> colorToString;
        /**
         * Map statique utilisée pour l'enregistrement d'une sauvegarde vers un fichier JSON
         */
        static map<Type, string> typeToString;

        /**
         * Alias pour le type de la map utilisée pour le stockage des données du plateau.
         */
        using cellmap = unordered_map<Position, pair<const Cell*, unsigned int>, PositionHasher>;
        /**
         * Map contenant les données du plateau
         */
        cellmap cells;
        /**
         * Coordonnées du coin supérieur gauche du plateau.
         * Attribut actualisé lors d'un appel à setCell(), permettant d'avoir un point de repère pour l'affichage.
         */
        Position corner_tl;
        /**
         * Coordonnées du coin inférieur droit du plateau.
         * Attribut actualisé lors d'un appel à setCell(), permettant d'avoir un point de repère pour l'affichage.
         */
        Position corner_br;
    public:
        /*
         *A faire
         */
        json toJsonBoard() const;

        /*
         *A faire
         */
        static Board fromJsonBoard(const json& j);

        /**
         * Itérateur sur les données du plateau.
         * L'itérateur héritant d'un itérateur de unordered_map, l'ordre du passage des éléments n'est pas garanti.
         */
        class iterator : public cellmap::iterator {
            friend class Board;
            explicit iterator(cellmap::iterator mi) : cellmap::iterator(mi) {}
        };

        /**
         * Itérateur constant sur les données du plateau.
         * L'itérateur héritant d'un itérateur de unordered_map, l'ordre du passage des éléments n'est pas garanti.
         */
        class const_iterator : public cellmap::const_iterator {
            friend class Board;
            explicit const_iterator(cellmap::const_iterator mi) : cellmap::const_iterator(mi) {}
        };

        /**
         * @return Itérateur commençant le parcours du plateau
         */
        iterator begin() {return iterator(cells.begin());}
        /**
         * @return Itérateur indiquant la fin de parcours du plateau
         */
        iterator end() {return iterator(cells.end());}

        /**
         * @return Itérateur constant commençant le parcours du plateau
         */
        const_iterator begin() const {return const_iterator(cells.cbegin());}
        /**
         * @return Itérateur constant indiquant la fin de parcours du plateau
         */
        const_iterator end() const {return const_iterator(cells.cend());}

        /**
         * @return Itérateur constant commençant le parcours du plateau
         */
        const_iterator cbegin() const {return const_iterator(cells.cbegin());}
        /**
         * @return Itérateur constant indiquant la fin de parcours du plateau
         */
        const_iterator cend() const {return const_iterator(cells.cend());}

        /**
         * Constructeur de la classe Board. Par défaut, le plateau est vide.
         */
        Board();

        /**
         * Destructeur de la classe Board.
         */
        ~Board();

        /**
         * Constructeur par recopie de la classe Board.
         * @param b Board à recopier
         */
        Board(const Board& b);

        /**
         * Opérateur d'affectation de la classe Board.
         * @param b Board à recopier
         */
        Board& operator=(const Board&);

        /**
         * Accesseur en lecture de la case de position pos dans le Board.
         * @param pos Position de la case
         * @return Pointeur const sur la case de coordonnées pos. nullptr si aucune case à l'emplacement indiqué.
         */
        const Cell* getCell(const Position& pos) const;

        /**
         * Accesseur en lecture de la case de position pos dans le Board.
         * @param x Coordonnée x de la case
         * @param y Coordonnée y de la case
         * @return Pointeur const sur la case de coordonnées x et y. nullptr si aucune case à l'emplacement indiqué.
         */
        const Cell* getCell(int x, int y) const;

        /**
         * Accesseur en lecture sur la hauteur de la case de position pos dans le Board.
         * @param pos Position de la case
         * @return unsigned int représentant la hauteur de la case de coordonnées pos.
         * nullptr si aucune case à l'emplacement indiqué.
         */
        unsigned int getHeight(const Position& pos) const;
        /**
         * Accesseur en lecture sur la hauteur de la case de position pos dans le Board.
         * @param x Coordonnée x de la case
         * @param y Coordonnée y de la case
         * @return unsigned int représentant la hauteur de la case de coordonnées x et y.
         * nullptr si aucune case à l'emplacement indiqué.
         */
        unsigned int getHeight(int x, int y) const;

        /**
         * Accesseur en écriture de la case de position pos. Assigne l'emplacement pos à la case c et à la hauteur h.
         * @param pos Position de l'emplacement à écrire
         * @param h Hauteur à écrire
         * @param c Pointeur const vers la case à écrire
         */
        void setCell(const Position& pos, unsigned int h, const Cell* c);

        /**
         * Accesseur en écriture de la case d'emplacement x et y.
         * Assigne l'emplacement de coordonnées x et y à la case c et à la hauteur h.
         * @param x Coordonnée x de l'emplacement à écrire
         * @param y Coordonnée y de l'emplacement à écrire
         * @param h Hauteur à écrire
         * @param c Pointeur const vers la case à écrire
         */
        void setCell(int x, int y, unsigned int h, const Cell* c);

        /**
         * Accesseur en lecture des coins du plateau.
         * Les coins ne sont pas nécessairement des cases du plateau, mais plutôt des positions.
         * @return pair contenant le coin supérieur gauche et le coin inférieur droit, dans cet ordre.
         */
        std::pair<Position, Position> getCorners() const;
        friend ostream& operator<<(ostream& f, const Board& p);

    };

    /**
     * Fonction utilisée pour générer des string de la bonne taille pour les axes de l'affichage console.
     * @param x Entier à convertir
     * @return Chaîne de caractères
     */
    string lenStringInt(int x);

    /**
     * @param f Flux de sortie
     * @param p Plateau à afficher
     * @return Flux modifié
     */
    ostream& operator<<(ostream& f, const Board& p);

}


#endif //PROJETLO21A25_PLATEAU_H