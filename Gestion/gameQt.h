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

using namespace std;
namespace Eloise {
    /*
     *design patern singleton
     */
    class GameQt : public Game {
    private:
        QWidget* parent = nullptr;
        /*
         *static instance of GameQt
         */
        static GameQt* instanceQt;
        /*
         *constructor for a new game using constructor of Game
         */
        GameQt(size_t nb_players,string v) : Game(nb_players,v) {}
        /*
         *constructor for an old game using constructor of Game
         */
        GameQt(const Amalena::GameMemento& game_memento) : Game(game_memento) {}
    public:
        /*
         *method that returns the unique instance
         *@param number of players and version
         *@return instance
         */
        static GameQt& giveInstance(size_t nb_players,string v) {
            if (!instanceQt) instanceQt = new GameQt(nb_players,v);
            return *instanceQt;
        }
        /*
         *method that returns the unique instance
         *@param game memento
         *@return instance
         */
        static GameQt& giveInstance(const Amalena::GameMemento& game_memento) {
            if (!instanceQt) instanceQt = new GameQt(game_memento);
            return *instanceQt;
        }
        /*
         *method that frees the instance
         */
        static void freeInstance() {
            delete instanceQt;
            instanceQt = nullptr;
        }
        /*
         *method that creates a new player and adds it to the vector
         *@param name of player
         */
        void addPlayer(const string& name) override ;
        /*
         *method that asks the name of each player and then adds them to the game
         */
        void addEachPlayerToGame() override;
        /*
         *method that displays the name and the stones of player that plays using a message box
         */
        void displayCurrentPlayerInfo() override;
        /*
         *method that allows current player to play
         *@return a boolean that tells if he played (true) or if he left the game (false)
         *@param copies of river and board in order to cancel actions
         *player picks a tile and play (places it on his board with playTurn())
         *loop to cancel and restart while not satisfied
         */
        bool actionsPlayer(Amalena::River* river_copy,BoardManager* board_copy) override;
        /*
         *method that asks for the name of the solo player and adds it to game
         */
        void askNameSoloGame() override ;
        /*
         *method that creates the architect taking into account the difficulty
         *@param difficulty for score
         */
        void architectCreation(int difficulty) override ;
        /*
         *method that manages the actions of the architect
         *takes the first tile in the river w/ a PLACE in it
         *ensures that the architect has enough stones
         *handles the picking in the river and the update of the stones
         */
        void architectPlaySoloGame() override ;
        /*
         *method that allows solo player to play
         *@return a boolean that tells if he played (true) or if he left the game (false)
         *@param copies of river and board in order to cancel actions
         *player picks a tile and play (places it on his board with playTurn())
         *loop to cancel and restart while not satisfied
         */
        bool realPlayerPlaySoloGame(BoardManager* board_copy,Amalena::River* river_copy) override ;
        /*
         *method that displays the river
         */
        void displayRiver() override;
        /*
         *method that allows to choose and pick a tile in river thanks to giveTile()
         *@return the chosen tile
         *update the amount of stones
         */
        Tile& chooseTileRiver() override ;
        /*
         *method that allows player to choose a pseudo for the game
         *@return the pseudo
         */
        string displayAbandonGame1() override;
        /*
         *method that display a confirmation that the game is saved
         */
        void displayAbandonGame2() override;
    };
}
#endif //PROJETLO21A25_GAMEQT_H