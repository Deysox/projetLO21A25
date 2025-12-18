//
// Created by elobo on 10/12/2025.
//

#ifndef PROJETLO21A25_PLAYERQT_H
#define PROJETLO21A25_PLAYERQT_H
#include "player.h"
#include <QObject>
using namespace Barnabe;
namespace Eloise {
    class PlayerQt : public QObject , public Player {
        Q_OBJECT
    public:
        /*
         *constructor that calls Player constructor
         *@param parent : a QObject*
         *@param s : reference of player name
         */
        PlayerQt(const string& s,  QObject* parent = nullptr) : QObject(parent), Player(s) {}
        /*
         *method that emits a boardDisplay signal
         */
        void displayBoard() override;
        /*
         *method that allows player to choose a position and a rotation
         *then calls place() method to actually place tile
         *then updates the amount of stones
         *@param reference of chosen tile
         */
        void placeTile(const Tile& tile) override;
        signals:
            void boardDisplay(const QString &boardText);
    };
    /*
     *class used for solo variant
     */
    class ArchitectQt : public PlayerQt {
        /*
         *attribut difficulty for score
         */
        int difficulty;
        /*
         *attribut which is simply a vector of tiles because architect doesn't have to place his tile
         */
        vector <Tile*> architect_tiles;
    public:
        /*
         *constructor of architect
         *uses PlayerQt constructor
         *@param name : name of player
         *@param d : difficulty for score
         *@param parent : a QObject*
         */
        ArchitectQt(const std::string& name, int d, QObject* parent = nullptr)
            : PlayerQt(name,parent), difficulty(d) {}
        /*
         *override of playTurn()
         *during his turn architect has only to add tiles to his vector
         */
        void playTurn(const Tile& t) override {
            architect_tiles.push_back(const_cast<Tile*>(&t));
        }
    };
}
#endif //PROJETLO21A25_PLAYERQT_H