//
// Created by elobo on 10/12/2025.
//

#ifndef PROJETLO21A25_GAMECONSOLE_H
#define PROJETLO21A25_GAMECONSOLE_H
#include "game.h"

using namespace std;
/*
 *design pattern singleton
 */
class GameConsole : public Game {
private:
    /*
     *static instance
     */
    static GameConsole* instanceConsole;
    /*
     *constructor for new game
     */
    GameConsole(size_t nb_players,string v) : Game(nb_players,v) {}
    /*
     *constructor to resume a game
     */
    GameConsole(const Amalena::GameMemento& game_memento) : Game(game_memento) {}
public:
    /*
     *static method that return the instance
     */
    static GameConsole& giveInstance(size_t nb_players,string v) {
        if (!instanceConsole) instanceConsole = new GameConsole(nb_players,v);
        return *instanceConsole;
    }
    /*
     *static method that return the instance
     */
    static GameConsole& giveInstance(const Amalena::GameMemento& game_memento) {
        if (!instanceConsole) instanceConsole = new GameConsole(game_memento);
        return *instanceConsole;
    }
    /*
    *static method that frees the instance
    */
    static void freeInstance() {
        delete instanceConsole;
        instanceConsole = nullptr;
    }
    /*
     *method that creates a new player and adds it to the vector
     */
    void addPlayer(const string& name) override;
    /*
    *method that asks for the names of the players and calls addPlayer()
    */
    void addEachPlayerToGame() override;
    /*
    *method that displays the information of the player using << operator
    */
    void displayCurrentPlayerInfo() override;
    /*
    *method that displays the information of the player using << operator
    */
    bool actionsPlayer(Amalena::River* river_copy,BoardManager* board_copy) override;
    /*
    *method that asks if the player wants to abandon
    *then allows him to pick a tile thanks to pickRiver()
    *then asks playTurn() so that he actually plays
    *loop while the player is not satisfied of his actions
    */
    /*
     *method that asks the solo player his name and calls addPlayer()
     */
    void askNameSoloGame() override ;
    /*
     *method that creates the architect takin into account the difficulty level
     */
    void architectCreation(int difficulty) override ;
    /*
     *method that manages the actions of the architect during his turn
     *architect chooses the first tile in a river w/ a PLACE
     *if he can't afford it or if there is no PLACE then he takes the first one
     *then method calls giveTile() method so that the river gives the tile
     *method updates the amount of stones he's got left
     */
    void architectPlaySoloGame() override ;
    /*
     *method that manages the turn of the solo player
     *counts the stones he lost to give them to the architect
     *allows player to pick a tile and place it
     *allows player to discard his actions and do it again while not satisfied
     *takes as parameters copies of board and river so that he can cancel his actions
     */
    bool realPlayerPlaySoloGame(BoardManager* board_copy,Amalena::River* river_copy) override ;
    /*
    *method that display the river thanks to << operator
    */
    void displayRiver() override;
    /*
     *method that allows player to select a pile in the river
     *updates the amount of stones
     */
    Tile& chooseTileRiver() override;
    /*
     *method that retrieve the pseudo of the game abandoned
     *asks the player to choose a pseudo and returns it
     */
    string displayAbandonGame1() override;
    void displayAbandonGame2() override;
};
#endif //PROJETLO21A25_GAMECONSOLE_H