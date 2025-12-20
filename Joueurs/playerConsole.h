//
// Created by elobo on 10/12/2025.
//

#ifndef PROJETLO21A25_PLAYERCONSOLE_H
#define PROJETLO21A25_PLAYERCONSOLE_H
#include "player.h"
using namespace Barnabe;
namespace Eloise{
    /**
     * Classe fille de Player pour la version console
     */
    class PlayerConsole : public Player {
    public:
        /**
         * Constructeur du joueur
         * @param s le nom du joueur
         */
        PlayerConsole(const string& s) : Player(s){}

        /**
         * Méthode pour afficher le plateau
         */
        void displayBoard() override;

        /**
         * Méthode pour placer la tuile
         * @param tile référence sur la tuile à placer
         */
        void placeTile(const Tile &tile) override;
    };

    /**
     * Classe architecte pour la version console
     * Permet de gérer l'illustre architecte pour la variante solo
     */
    class ArchitectConsole : public PlayerConsole {
        /**
         * Attribut difficulty pour le compte du score
         */
        int difficulty;
        /**
         * Vecteur de tuiles car l'architecte n'ajoute pas vraiment ses tuiles au plateau
         */
        vector <Tile*> architect_tiles;
    public:
        /**
         * Constructeur de l'architecte
         * @param name
         * @param d la difficulté pour le compte du score
         */
        ArchitectConsole(const std::string& name, int d)
            : PlayerConsole(name), difficulty(d) {}

		/**
		 * Getteur du vecteur de Tile
		 * @return le Vecteur de Tiles de l'architecte
		 */
		const vector<Tile*>& getArchitetctTiles() const {return architect_tiles;}

        /**
         * Méthode qui ajoute la tuile choisie au vecteur de tuiles
         * @param t référence sur la tuile à placer
         */
        void playTurn(const Tile& t) override {
            architect_tiles.push_back(const_cast<Tile*>(&t));
        }
    };
}
#endif //PROJETLO21A25_PLAYERCONSOLE_H