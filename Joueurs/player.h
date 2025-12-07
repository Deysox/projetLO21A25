//
// Created by elobo on 29/11/2025.
//

#ifndef PROJETLO21A25_PLAYER_H
#define PROJETLO21A25_PLAYER_H
#include "../Plateau/board.h"
#include "../Plateau/boardmanager.h"
#include <string>
#include <QWidget>
#include <QObject>
#include <QString>

//missing score in attributs' list
namespace Barnabe {
    class Player : public QObject {
        Q_OBJECT
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
        void playTurnQt(const Tile& tile, QWidget* parent = nullptr);
        //method for score missing, to be added
        signals:
            void boardDisplay(const QString &boardText);
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

#endif //PROJETLO21A25_PLAYER_H