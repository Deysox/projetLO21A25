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

//missing score in attributs' list
namespace Eloise {
    /*
     *desing pattern template method
     */
    class Player {
    protected:
        /*
         *static attribut that allows the good initial distribution of stones at the beginning
         */
        static size_t stones_distribution;
        /*
         *name of player attribut
         */
        string name;
        /*
         *board attribut
         *type is BoardManager that handles the good management of the board
         */
        Barnabe::BoardManager board;
        /*
         *attribut that indicates the number of stones held by player
         */
        int stones;
    public:
        /*
         *constructor that creates a player w/ his name
         *@param name of player
         */
        Player(const string& s);
        /*
         *virtual destructor because of inheritance
         */
        virtual ~Player();
        /*
         *name getter
         */
        const string& getName() const;
        /*
         *stones getter
         */
        int getStones() const;
        /*
         *board getter
         */
        const Barnabe::BoardManager& getBoard() const;
        /*
         *board setter
         */
        void setBoard(const Barnabe::BoardManager& b){board = b;}
        /*
         *stones setter
         */
        void setStones(int n);
        /*
         *method that updates the amount of stones by adding some
         *@param number of stones added
         */
        void addStones(int n);
        /*
         *template method
         *@param reference of chosen tile
         *displays the board before and after placing the tile
         */
        virtual void playTurn(const Barnabe::Tile& tile) {
            displayBoard();
            placeTile(tile);
            displayBoard();
        }
        /*
         *displaying of board different if console or qt
         *method implemented by playerConsole and playerQt
         */
        virtual void displayBoard() = 0;
        /*
         *placement of tile different if console or qt
         *method implemented by playerConsole and playerQt
         */
        virtual void placeTile(const Barnabe::Tile& tile) = 0;
    };
    /*
     *operator to display player and his information
     */
    ostream& operator<<(ostream& f, const Player& p);
}

#endif //PROJETLO21A25_PLAYER_H