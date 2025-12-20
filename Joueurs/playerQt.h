//
// Created by elobo on 10/12/2025.
//

#ifndef PROJETLO21A25_PLAYERQT_H
#define PROJETLO21A25_PLAYERQT_H
#include "player.h"
#include <QObject>
#include "../Plateau/QT/boardqt.h"

namespace Eloise {
    class PlayerQt : public QObject , public Player {
        Q_OBJECT
    public:
        BoardQt* BoardWidget=nullptr;
        QWidget* window =nullptr;
        PlayerQt(const string& s,  QObject* parent = nullptr) : QObject(parent), Player(s) {}
        void displayBoard() override;
        void placeTile(const Tile& tile) override;
    };
    class ArchitectQt : public PlayerQt {
        int difficulty;
        vector <Tile*> architect_tiles;
    public:
        ArchitectQt(const std::string& name, int d, QObject* parent = nullptr)
            : PlayerQt(name,parent), difficulty(d) {}
        void playTurn(const Tile& t) override {
            architect_tiles.push_back(const_cast<Tile*>(&t));
        }
    };
}
#endif //PROJETLO21A25_PLAYERQT_H