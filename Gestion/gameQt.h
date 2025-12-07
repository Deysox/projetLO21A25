//
// Created by elobo on 06/12/2025.
//

#ifndef PROJETLO21A25_GAMEQT_H
#define PROJETLO21A25_GAMEQT_H
#include <string>
#include <vector>
#include "../Chantier/river.h"
#include "../Joueurs/player.h"
#include "../Chantier/pile.h"
#include "../Tuiles/deck.h"
#include "../Gestion/game.h"
#include <QWidget>

using namespace std;

class GameQt : public Game {
private:
    static GameQt* instanceQt;
    GameQt(size_t nb_players) : Game(nb_players) {}

public:
    static GameQt& giveInstance(size_t nb_players) {
        if (!instanceQt) instanceQt = new GameQt(nb_players);
        return *instanceQt;
    }

    static void freeInstance() {
        delete instanceQt;
        instanceQt = nullptr;
    }
    void manageGameQt(QWidget* parent = nullptr);
    void manageSoloGameQt(int difficulty, QWidget* parent = nullptr);
    Tile& pickRiverQt(QWidget* parent = nullptr);
};
#endif //PROJETLO21A25_GAMEQT_H