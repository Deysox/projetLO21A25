//
// Created by elobo on 29/11/2025.
//

#ifndef PROJETLO21A25_PLAYER_H
#define PROJETLO21A25_PLAYER_H
#include "../Tuiles/tile.h"
#include "../Plateau/board.h"
#include "../Plateau/boardmanager.h"
#include <string>
#include <QWidget>
#include <QObject>
#include <QString>

using namespace Barnabe;
namespace Eloise {
    /**
     * Classe abstraite du joueur
     * Design pattern template method
     */
    class Player {
    protected:
        /**
         * Attribut static qui s'incrémente pour la distribution des pierres
         */
        static size_t stones_distribution;
        /**
         * Nom du joueur
         */
        string name;
        /**
         * Plateau du joueur
         */
        BoardManager board;
        /**
         * Nombre de pierres détenues
         */
        int stones;
    public:
        /**
         * Contructeur du joueur
         * @param s le nom du joueur
         */
        Player(const string& s);

        /**
         * Destructeur virtuel car héritage
         */
        virtual ~Player();

        /**
         * Getter du nom du joueur
         * @return référence sur le nom
         */
        const string& getName() const;

        /**
         * Getter du nombre de pierres
         * @return le nombre de pierres
         */
        int getStones() const;

        /**
         * Getter du plateau
         * @return référence sur le plateau
         */
        const BoardManager& getBoard() const;

        /**
         * Setter du plateau
         * @param b le plateau
         */
        void setBoard(const BoardManager& b){board = b;}

        /**
         * Setter du nombre de pierres
         * @param n le nombre de pierres
         */
        void setStones(int n);

        /**
         * Méthode qui ajoute un certain nombre de pierres
         * @param n le nombre de pierres à ajouter
         */
        void addStones(int n);

        /**
         * Template method
         * Méthode qui affiche le plateau et permet de placer une tuile dessus
         * @param tile référence sur la tuile à placer
         */
        virtual void playTurn(const Tile& tile) {
            displayBoard();
            placeTile(tile);
            displayBoard();
        }

        /**
         * Méthode virtuelle pure pour afficher le plateau
         */
        virtual void displayBoard() = 0;

        /**
         * Méthode qui permet de placer la tuile sur le plateau
         * @param tile référence sur la tuile à placer
         */
        virtual void placeTile(const Tile& tile) = 0;
    };

    /**
     * Surcharge de l'opérateur << pour afficher le joueur
     * @param f le flux
     * @param p le joueur
     * @return un flux
     */
    ostream& operator<<(ostream& f, const Player& p);
}

#endif //PROJETLO21A25_PLAYER_H