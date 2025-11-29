#ifndef PROJETLO21A25_JOUEUR_H
#define PROJETLO21A25_JOUEUR_H

#include "../Plateau/board.h"
#include "../Plateau/boardmanager.h"
#include <string>

//attribut stones à changer ==> mettre un attribut de type ScoreGeneral
namespace Barnabe {
    class Player {
        //parameter that allows the good initial distribution of stones
        static size_t stones_distribution;
        string name;
        BoardManager board;
        int stones;
    public:
        Player(const string& s);
        ~Player();
        const string& getName() const;
        int getStones() const;
        const BoardManager& getBoard() const;
        void setStones(int n);
        void addStones(int n);
        bool playTurn(const ClassicTile&);
        //int score() const;
    };

    enum class Difficulty {EASY = 0, MEDIUM = 1, HARD = 2};

    class Architect : public Player {
        Difficulty difficulty;
    public:

    };
    ostream& operator<<(ostream& f, const Player& p);
}




#endif //PROJETLO21A25_JOUEUR_H