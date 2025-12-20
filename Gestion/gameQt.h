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
        /**
         * Instance unique
         */
        static GameQt* instanceQt;
        /**
         * Contructeur pour lancer une partie
         * @param nb_players le nombre de joueurs
         * @param v la ou les variantes
         */
        GameQt(size_t nb_players,string v) : Game(nb_players,v) {}
        /**
         * Constructeur pour reprendre une partie
         * @param game_memento
         */
        GameQt(const Amalena::GameMemento& game_memento) : Game(game_memento) {}
    public:
        /**
         * Méthode pour récupérer l'instance unique et la créer si elle n'existe pas
         * @param nb_players
         * @param v
         * @return référence sur instance unique
         */
        static GameQt& giveInstance(size_t nb_players,string v) {
            if (!instanceQt) instanceQt = new GameQt(nb_players,v);
            return *instanceQt;
        }
        /**
         * Méthode pour récupérer l'instance unique et la créer si elle n'existe pas
         * @param game_memento le game memento avec toutes les informations
         * @return référence sur instance unique
         */
        static GameQt& giveInstance(const Amalena::GameMemento& game_memento) {
            if (!instanceQt) instanceQt = new GameQt(game_memento);
            return *instanceQt;
        }

        /**
         * Méthode pour libérer l'instance unique
         */
        static void freeInstance() {
            delete instanceQt;
            instanceQt = nullptr;
        }

        /**
         * Méthode qui crée et ajoute le joueur au vecteur
         * @param name du joueur
         */
        void addPlayer(const string& name) override ;

        /**
         * Méthode qui fait une boucle pour ajouter chacun des joueurs
         */
        void addEachPlayerToGame() override;

        /**
         * Méthode qui affiche les informations du joueur courant
         */
        void displayCurrentPlayerInfo() override;

        /**
         * Méthode qui permet au joueur de piocher, de placer sa tuile et éventuellement de se raviser
         * @param river_copy
         * @param board_copy
         * @return un booléen à true si on continue la partie, à false si on l'interrompt
         */
        bool actionsPlayer(Amalena::River* river_copy,BoardManager* board_copy) override;

        /**
         * Méthode qui demande son nom au joueur solo et qui l'ajoute à la partie
         */
        void askNameSoloGame() override ;

        /**
         * Méthode qui crée l'architecte
         * @param difficulty la difficulté pour le score
         */
        void architectCreation(int difficulty) override ;

        /**
         * Méthode qui régit le tour de l'architecte
         */
        void architectPlaySoloGame() override ;

        /**
         * Méthode qui permet au joueur solo de piocher sa tuile, de la placer, de se raviser
         * @param board_copy une copie du plateau avant le tour
         * @param river_copy une copie de la rivière avant le tour
         * @return un booléen qui indique si on continue ou pas
         */
        bool realPlayerPlaySoloGame(BoardManager* board_copy,Amalena::River* river_copy) override ;

        /**
         * Méthode qui affiche la rivière
         */
        void displayRiver() override;

        /**
         * Méthode qui permet de prendre une tuile dans la rivière
         * @return la référence sur la tuile choisie
         */
        Tile& chooseTileRiver() override ;

        /**
         * Méthode qui demande le pseudo de la partie abandonnée
         * @return le pseudo de la partie enregistrée
         */
        string displayAbandonGame1() override;

        /**
         * Méthode qui affiche une confirmation de l'enregistrement
         */
        void displayAbandonGame2() override;
    };
}
#endif //PROJETLO21A25_GAMEQT_H