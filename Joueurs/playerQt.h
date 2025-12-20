//
// Created by elobo on 10/12/2025.
//

#ifndef PROJETLO21A25_PLAYERQT_H
#define PROJETLO21A25_PLAYERQT_H
#include "player.h"
#include <QObject>

namespace Eloise {
    /**
     * Classe fille de player pour la version Qt
     */
    class PlayerQt : public QObject , public Player {
        Q_OBJECT
    public:
        /**
         * Constructeur du joueur pour la version Qt
         * @param s le nom
         * @param parent pour Qt
         */
        PlayerQt(const string& s,  QObject* parent = nullptr) : QObject(parent), Player(s) {}

        /**
         * Méthode qui affiche le plateau
         */
        void displayBoard() override;

        /**
         * Méthode qui permet de place la tuile choisie
         * @param tile référence sur la tuile à placer
         */
        void placeTile(const Tile& tile) override;
        signals:
            void boardDisplay(const QString &boardText);
    };

    /**
     * Classe Architect de la version Qt
     * Permet de gérer le comportement de l'illustre architecte dans la variante solo
     */
    class ArchitectQt : public PlayerQt {
        /**
         * Attribut difficulté pour le score
         */
        int difficulty;
        /**
         * Vecteur de tuiles pour stocker les tuiles car il ne les place pas vraiment
         */
        vector <Tile*> architect_tiles;
    public:
        /**
         * Constructeur
         * @param name
         * @param d la difficulté
         * @param parent
         */
        ArchitectQt(const std::string& name, int d, QObject* parent = nullptr)
            : PlayerQt(name,parent), difficulty(d) {}

        /**
         * Méthode pour ajouter une tuile au vecteur
         * @param t référence sur la tuile
         */
        void playTurn(const Tile& t) override {
            architect_tiles.push_back(const_cast<Tile*>(&t));
        }
    };
}
#endif //PROJETLO21A25_PLAYERQT_H