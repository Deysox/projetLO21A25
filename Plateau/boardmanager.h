#ifndef PROJETLO21A25_PLACEMENT_H
#define PROJETLO21A25_PLACEMENT_H

#include "../Utilitaires/position.h"
#include "../Utilitaires/rotation.h"
#include "board.h"
#include "../Tuiles/tile.h"



namespace Barnabe {
    //using namespace Marilou;


    /**
     * Classe de gestion du plateau d'Akropolis par un joueur humain.
     * Le BoardManager agit comme une passerelle entre le Player et le Board.
     *
     * BoardManager gère le cycle de vie de Board et StartingTile
     */
    class BoardManager {
        /**
         * Plateau associé au BoardManager sur lequel il réalise les opérations.
         */
        Board* board;
        /**
         * Attribut correspondant à la tuile de départ créée lors de l'initialisation du plateau.
         */
        StartingTile* startingTile;
    public:
        /**
         * Constructeur de la classe BoardManager.
         * Initialise un plateau possédant une tuile de départ.
         */
        BoardManager();
        /**
         * Constructeur par recopie de la classe Board.
         */
        BoardManager(const BoardManager& e);
        /**
         * Destructeur de la classe Board.
         * Désalloue l'espace octroyé au plateau et à la tuile de départ
         */
        virtual ~BoardManager();

        /*
         * Commenter ici
         */
        explicit BoardManager(const Board& b) : board(new Board(b)), startingTile(new StartingTile()) {}

        /**
         * Opérateur d'affectation du BoardManager
         */
        BoardManager& operator=(const BoardManager& e);

        /**
         * Renvoie un pointeur vers le plateau géré par le BoardManager
         * @return Pointeur vers plateau
         */
        [[nodiscard]] const Board* getBoard() const {return board;}

        /**
         * Place la tuile à la position/rotation souhaitée dans le plateau.
         * Lève une exception si c'est impossible.
         * @param t Un pointeur const vers une tuile à placer dans le plateau.
         * @param p La position de la tuile pivot dans le plateau
         * @param r La rotation de la tuile autour de la tuile pivot
         * @param adjacentIgnore Si est à true, la contrainte d'adjacence de la tuile placée avec le reste du plateau
         * sera ignorée.
         * @returns Nombre de pierres obtenues par le joueur par recouvrement de carrières
         */
        virtual int place(const Tile* t, const Position& p, const Rotation& r, bool adjacentIgnore = false);

        /*
         * Ici aussi
         */
        void setBoard(const BoardManager& bm) {
            delete board;
            board = new Board(*bm.board);
            startingTile = new StartingTile();
            place(startingTile,Position(0,0),0, true);
        }

        friend ostream& operator<<(ostream& f, const BoardManager& c);
    };

    /**
     *
     * @param f Flux de sortie
     * @param c BoardManager (plateau) à afficher
     * @return Flux modifié
     */
    ostream& operator<<(ostream& f, const BoardManager& c);

}



#endif //PROJETLO21A25_PLACEMENT_H