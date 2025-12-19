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
    class Player {
    protected:
        //parameter that allows the good initial distribution of stones
        static size_t stones_distribution;
        string name;
        BoardManager board;
        int stones;
    public:
        Player(const string& s);
        virtual ~Player();
        const string& getName() const;
        int getStones() const;
        const BoardManager& getBoard() const;
        void setBoard(const BoardManager& b){board = b;}
        void setStones(int n);
        void addStones(int n);
        virtual void playTurn(const Tile& tile) {
            displayBoard();
            placeTile(tile);
            displayBoard();
        }
        virtual void displayBoard() = 0;
        virtual void placeTile(const Tile& tile) = 0;
    };
    ostream& operator<<(ostream& f, const Player& p);
}

#endif //PROJETLO21A25_PLAYER_H