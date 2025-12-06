//
// Created by elobo on 29/11/2025.
//

#ifndef TEST29_11_PLAYER_H
#define TEST29_11_PLAYER_H
#include "../Plateau/board.h"
#include "../Plateau/boardmanager.h"
#include <string>
#include <QWidget>

//attribut stones à changer ==> mettre un attribut de type ScoreGeneral
namespace Eloise {
    using namespace Barnabe;

    class Player {
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
        virtual void playTurn(const Tile&);
        void Player::playTurnQt(const Tile& tile, QWidget* parent);
        //int score() const;
    };

    //solo variant
    class Architect : public Player {
        int difficulty;
        vector <Tile*> architect_tiles;
    public:
        Architect(const std::string& name, int d)
            : Player(name), difficulty(d) {}
        void playTurn(const Tile& t) override;
    };
    ostream& operator<<(ostream& f, const Player& p);
}

#endif //TEST29_11_PLAYER_H