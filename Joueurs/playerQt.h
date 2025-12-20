//
// Created by elobo on 10/12/2025.
//

#ifndef PROJETLO21A25_PLAYERQT_H
#define PROJETLO21A25_PLAYERQT_H
#include "player.h"
#include <QObject>
#include "../Plateau/QT/boardqt.h"

namespace Eloise {
    /**
     * Classe fille de Player pour la version console
     */
    class PlayerQt : public QObject , public Player {
        Q_OBJECT
    public:
        BoardQt* BoardWidget=nullptr;
        QWidget* window =nullptr;
        /**
         * Constructeur
         * @param s le nom
         * @param parent
         */
        PlayerQt(const string& s,  QObject* parent = nullptr) : QObject(parent), Player(s) {}
        void displayBoard() override;
        void placeTile(const Tile& tile) override;
    };
    /**
     * Classe architecte pour la version qt
     * Permet de gérer l'illustre architecte pour la variante solo
     */
    class ArchitectQt : public PlayerQt {
        /**
         * Attribut difficulté pour le score
         */
        int difficulty;
        /**
         * Vecteur de tuiles car l'architecte ne place pas vraiment ses tuiles sur un plateau
         */
        vector <Tile*> architect_tiles;
    public:
        /**
         * Constructeur
         * @param name
         * @param d difficulté
         * @param parent
         */
        ArchitectQt(const std::string& name, int d, QObject* parent = nullptr)
            : PlayerQt(name,parent), difficulty(d) {}

        /**
         * Méthode qui permet d'ajouter la tuile choisie au vecteur
         * @param t référence sur tuile
         */
        void playTurn(const Tile& t) override {
            architect_tiles.push_back(const_cast<Tile*>(&t));
        }
    };
}
#endif //PROJETLO21A25_PLAYERQT_H