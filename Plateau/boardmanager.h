#ifndef PROJETLO21A25_PLACEMENT_H
#define PROJETLO21A25_PLACEMENT_H

#include <map>
#include <vector>
#include <string>

#include "../Utilitaires/position.h"
#include "../Utilitaires/rotation.h"
#include "board.h"

using namespace std;


namespace Barnabe {
    //using namespace Marilou;


    /*
     * Classe de gestion du plateau d'Akropolis par un joueur humain.
     * Le BoardManager agit comme une passerelle entre le Player et le Board.
     *
     */
    class BoardManager {
        /*
         * Plateau associé au BoardManager sur lequel il réalise les opérations.
         */
        Board* board;
        /*
         * Attribut correspondant à la tuile de départ créée lors de l'initialisation du plateau.
         */
        StartingTile* startingTile;
    public:
        /*
         * Constructeur de la classe BoardManager.
         * Initialise un plateau possédant une tuile de départ.
         */
        BoardManager();
        /*
         * Constructeur par recopie de la classe Board.
         */
        BoardManager(const BoardManager& e);
        /*
         * Destructeur de la classe Board.
         * Désalloue l'espace octroyé au plateau et à la tuile de départ
         */
        ~BoardManager();

        /*
         * Opérateur d'affectation du BoardManager
         */
        BoardManager& operator=(const BoardManager& e);


        /*
         * Vérifie si une tuile peut être placée à la position souhaitée en argument.
         * @param t Un pointeur const vers une tuile à placer dans le plateau.
         * @param p La position de la tuile pivot dans le plateau
         * @param r La rotation de la tuile autour de la tuile pivot
         * @return true si la tuile peut être placée, false sinon.
         */
        bool canPlace(const ClassicTile* t, Position p, Rotation r, bool adjacentIgnore = false) const;

        /*
         * Place la tuile à la position/rotation souhaitée dans le plateau.
         * Lève une exception si c'est impossible.
         * @param t Un pointeur const vers une tuile à placer dans le plateau.
         * @param p La position de la tuile pivot dans le plateau
         * @param r La rotation de la tuile autour de la tuile pivot
         */
        void place(const ClassicTile* t, Position p, Rotation r, bool adjacentIgnore = false);


        /*
         * Renvoie le score associé au plateau.
         * @return int Score
         */
        int boardScore() const;

        friend ostream& operator<<(ostream& f, const BoardManager& c);
    };

    ostream& operator<<(ostream& f, const BoardManager& c);


    //class BoardManagerArchitect : public BoardManager;
}



#endif //PROJETLO21A25_PLACEMENT_H