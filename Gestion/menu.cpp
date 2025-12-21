#include "menu.h"
#include "gameQt.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QString>
#include <QDialog>
#include <QLineEdit>
#include <QtGui>
#include <QMessageBox>
#include <QObject>
#include <QInputDialog>

namespace Eloise {
    MenuQt::MenuQt(QWidget* parent) : QWidget(parent) {
        //Boutons
        boutonLancerGame = new QPushButton("Launch a game");
        boutonReprendreGame = new QPushButton("Resume a game");
        boutonAfficherRegles = new QPushButton("Display rules");

        //layout pour affichage
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(boutonLancerGame);
        layout->addSpacing(15);
        layout->addWidget(boutonReprendreGame);
        layout->addSpacing(15);
        layout->addWidget(boutonAfficherRegles);
        setLayout(layout);
        setWindowTitle("Menu du jeu");

        //connections
        connect(boutonAfficherRegles, &QPushButton::clicked,
            this, &MenuQt::boutonAfficherReglesClique);
        connect(boutonLancerGame, &QPushButton::clicked,
            this, &MenuQt::boutonLancerGameClique);
        connect(boutonReprendreGame, &QPushButton::clicked,
            this, &MenuQt::boutonReprendreGameClique);
    }

    void MenuQt::boutonAfficherReglesClique() {
        QMessageBox::information(this,
            "Rules",
            "In this tile-laying game, players take on the role of architects who compete against each other "
                   "by each creating a city using city tiles. Each city tile is composed of 3 "
                   "construction hexagons, each hexagon representing a neighbourhood, a square or a quarry. "
                   "There are several types of neighbourhood. Each neighbourhood earns victory points "
                   "if they are correctly placed according to their type.");
    }

    void MenuQt::boutonLancerGameClique() {

        int nb_players = QInputDialog::getInt(this,
                                              "Nombre de joueurs",
                                              "Number of players ? (1-4)",
                                              1,
                                              1,
                                              Game::getNbPlayersMax(),
                                              1);
        bool ok{}; string s = "";
        QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                             tr("Variante(s)"), QLineEdit::Normal,
                                             "", &ok);
        if (ok && !text.isEmpty())
            s = text.toStdString();
        if (nb_players != 1) {

            GameQt& game = GameQt::giveInstance(nb_players,s);
            //la partie se déroule
            game.manageGame();
            //affichage score
            game.endGame();
        }
        //version solo
        else {
            GameQt& game = GameQt::giveInstance(nb_players+1,s);
            int difficulty = QInputDialog::getInt(this,
                                                  "Difficulty",
                                                  "Difficulty ? (1 = easy, 2 = medium, 3 = hard)",
                                                  1, 1, 3, 1);
            //la partie se déroule
            game.manageSoloGame(difficulty);
            //affichage score
            game.endGame();
        }
        GameQt::freeInstance();
    }



    void MenuQt::boutonReprendreGameClique() {
        QString pseudo_game = QInputDialog::getText(this, "Game", "What was the pseudo of your game ?");
        string game_name = pseudo_game.toStdString();
        Amalena::savemanager save_manager;
        //appel à restore() avec pseudo saisi
        Amalena::GameMemento* game_memento = save_manager.restore(game_name);
        if (game_memento) {
            //sécurité, instance unique
            GameQt::freeInstance();
            //instance de game version qt
            GameQt& game = GameQt::giveInstance(*game_memento);
            //la partie se déroule
            game.manageResumeGame();
            //affichage score
            game.endGame();
            GameQt::freeInstance();
        }
    }
}