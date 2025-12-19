//
// Created by elobo on 10/12/2025.
//

#ifndef PROJETLO21A25_GAMECONSOLE_H
#define PROJETLO21A25_GAMECONSOLE_H
#include "game.h"
namespace Eloise {
    using namespace std;

    /**
     * Design pattern singleton
     * Classe fille de Game pour la version console
     */
    class GameConsole : public Game {
    private:
        /**
         * Instance unique
         */
        static GameConsole* instanceConsole;
        /**
         * Constructeur pour lancer une nouvelle partie
         * @param nb_players le nombre de joueurs
         * @param v la ou les variantes
         */
        GameConsole(size_t nb_players,string v) : Game(nb_players,v) {}
        /**
         * Constructeur pour reprendre une partie
         * @param game_memento
         */
        GameConsole(const Amalena::GameMemento& game_memento) : Game(game_memento) {}
    public:

        /**
         * Méthode pour accéder à l'instance unique
         * @param nb_players le nombre de joueurs
         * @param v la ou les variantes
         * @return référence sur l'instance unique
         */
        static GameConsole& giveInstance(size_t nb_players,string v) {
            if (!instanceConsole) instanceConsole = new GameConsole(nb_players,v);
            return *instanceConsole;
        }

        /**
         * Méthode pour accéder à l'instance unique
         * @param game_memento
         * @return référence sur l'instance
         */
        static GameConsole& giveInstance(const Amalena::GameMemento& game_memento) {
            if (!instanceConsole) instanceConsole = new GameConsole(game_memento);
            return *instanceConsole;
        }

        /**
         * Méthode qui libère l'instance unique
         */
        static void freeInstance() {
            delete instanceConsole;
            instanceConsole = nullptr;
        }

        /**
         * Méthode qui crée et ajoute un joueur
         * @param name
         */
        void addPlayer(const string& name) override;

        /**
         * Méthode qui boucle et ajoute chacun des joueurs
         */
        void addEachPlayerToGame() override;

        /**
         * Méthode qui affiche toutes les informations du joueur courant
         */
        void displayCurrentPlayerInfo() override;

        /**
         * Méthode qui permet au joueur d'effectuer toutes ses actions (pioche, placement, rollback) durant son tour
         * @param river_copy
         * @param board_copy
         * @return un booléen qui indique s'il faut continuer la partie ou la stopper
         */
        bool actionsPlayer(Amalena::River* river_copy,BoardManager* board_copy) override;

        /**
         * Méthode qui crée le joueur solo à partir du nom qu'il indique
         */
        void askNameSoloGame() override ;

        /**
         * Méthode qui crée l'architecte
         * @param difficulty difficulté pour le compte du score de l'architecte
         */
        void architectCreation(int difficulty) override ;

        /**
         * Méthode qui régie le tour de l'architecte
         */
        void architectPlaySoloGame() override ;

        /**
         * Méthode qui régit le tour du player solo
         * @param board_copy version originale du plateau avant le tour
         * @param river_copy version originale de la rivière avant le tour
         * @return
         */
        bool realPlayerPlaySoloGame(BoardManager* board_copy,Amalena::River* river_copy) override ;

        /**
         * Méthode qui affiche la rivière
         */
        void displayRiver() override;

        /**
         * Méthode pour choisir la tuile dans la rivière
         * @return référence sur la tuile choisie
         */
        Tile& chooseTileRiver() override;

        /**
         * Méthode qui permet de choisir le nom pour sauvegarder la partie
         * @return le pseudo de game choisi
         */
        string displayAbandonGame1() override;

        /**
         * Méthode qui affiche un message de confirmation
         */
        void displayAbandonGame2() override;
    };
}
#endif //PROJETLO21A25_GAMECONSOLE_H