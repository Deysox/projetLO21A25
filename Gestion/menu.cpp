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

MenuQt::MenuQt(QWidget* parent) : QWidget(parent) {
    //Boutons
    boutonLancerGame = new QPushButton("Launch a game");
    boutonReprendreGame = new QPushButton("Resume a game");
    boutonAfficherRegles = new QPushButton("Display rules");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(boutonLancerGame);
    layout->addSpacing(15);
    layout->addWidget(boutonReprendreGame);
    layout->addSpacing(15);
    layout->addWidget(boutonAfficherRegles);
    setLayout(layout);
    setWindowTitle("Menu du jeu");

    connect(boutonAfficherRegles, &QPushButton::clicked,
        this, &MenuQt::boutonAfficherReglesClique);
    connect(boutonLancerGame, &QPushButton::clicked,
        this, &MenuQt::boutonLancerGameClique);
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
        if (nb_players != 1) {
            GameQt& game = GameQt::giveInstance(nb_players);
            game.manageGame();
            game.endGame();
        }
        else {
            GameQt& game = GameQt::giveInstance(nb_players+1);
            int difficulty = QInputDialog::getInt(this,
                                                  "Difficulty",
                                                  "Difficulty ? (1 = easy, 2 = medium, 3 = hard)",
                                                  1, 1, 3, 1);
            game.manageSoloGame(difficulty);
        }
    GameQt::freeInstance();
}
