//
// Created by elobo on 10/12/2025.
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
#include <QObject>
namespace Eloise {
    using namespace std;

    /**
     * Design pattern singleton
     * Classe fille de Game pour la version Qt
     */
    class GameQt : public Game {
    private:
        QWidget* parent = nullptr;
        static GameQt* instanceQt;
        GameQt(size_t nb_players,string v) : Game(nb_players,v) {}
        GameQt(const Amalena::GameMemento& game_memento) : Game(game_memento) {}
    public:
        static GameQt& giveInstance(size_t nb_players,string v) {
            if (!instanceQt) instanceQt = new GameQt(nb_players,v);
            return *instanceQt;
        }
        static GameQt& giveInstance(const Amalena::GameMemento& game_memento) {
            if (!instanceQt) instanceQt = new GameQt(game_memento);
            return *instanceQt;
        }
        static void freeInstance() {
            delete instanceQt;
            instanceQt = nullptr;
        }

        //design pattern, template methods
        void addPlayer(const string& name) override ;
        void addEachPlayerToGame() override;
        void displayCurrentPlayerInfo() override;
        bool actionsPlayer(Amalena::River* river_copy,BoardManager* board_copy) override;

        void askNameSoloGame() override ;
        void architectCreation(int difficulty) override ;
        void architectPlaySoloGame() override ;
        bool realPlayerPlaySoloGame(BoardManager* board_copy,Amalena::River* river_copy) override ;

        void displayRiver() override;
        Tile& chooseTileRiver() override ;

        string displayAbandonGame1() override;
        void displayAbandonGame2() override;
    };
}
#endif //PROJETLO21A25_GAMEQT_H