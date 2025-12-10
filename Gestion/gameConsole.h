//
// Created by elobo on 10/12/2025.
//

#ifndef PROJETLO21A25_GAMECONSOLE_H
#define PROJETLO21A25_GAMECONSOLE_H
#include "game.h"

using namespace std;

class GameConsole : public Game {
private:
    static GameConsole* instanceConsole;
    GameConsole(size_t nb_players) : Game(nb_players) {}
public:
    static GameConsole& giveInstance(size_t nb_players) {
        if (!instanceConsole) instanceConsole = new GameConsole(nb_players);
        return *instanceConsole;
    }
    static void freeInstance() {
        delete instanceConsole;
        instanceConsole = nullptr;
    }
    void addPlayer(const string& name) override;

    void addEachPlayerToGame() override;
    void displayCurrentPlayerInfo() override;
    void actionsPlayer(Amalena::River* river_copy,BoardManager* board_copy) override;

    void askNameSoloGame() override ;
    void architectCreation(int difficulty) override ;
    void architectPlaySoloGame() override ;
    void realPlayerPlaySoloGame(BoardManager* board_copy,Amalena::River* river_copy) override ;

    void displayRiver() override;
    Tile& chooseTileRiver() override;
};
#endif //PROJETLO21A25_GAMECONSOLE_H