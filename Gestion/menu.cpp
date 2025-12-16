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
#include "../UI/init.h"

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
    initWidget = new init(this);
    initWidget->hide();

    connect(boutonAfficherRegles, &QPushButton::clicked,
        this, &MenuQt::boutonAfficherReglesClique);
    connect(boutonLancerGame, &QPushButton::clicked,
        this, &MenuQt::boutonLancerGameClique);
    connect(boutonReprendreGame, &QPushButton::clicked,
        this, &MenuQt::boutonReprendreGameClique);
    connect(initWidget, &init::gameparametersReady,this, &MenuQt::OnGameParameterReady);
    connect(initWidget, &init::sologameparametersReady,this, &MenuQt::OnSoloGameParameterReady);


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
    // methode pas forcément optimal ... à voir
    //ON cache le layout actuel_____________________________________________
    boutonLancerGame->hide();
    boutonReprendreGame->hide();
    boutonAfficherRegles->hide();
    //_____________puis affiche la fenetre d'initailisation_______________________________________________

    initWidget->show();
    /*int nb_players = QInputDialog::getInt(this,
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
        }*/
    //GameQt::freeInstance();
}
void MenuQt::OnGameParameterReady(int nbPlayers, QString variante, QStringList names )
{
    GameQt& game = GameQt::giveInstance(nbPlayers,variante.toStdString());
    //comme je ne peux pas transmettre plus d'info
    for (int i = 0; i < names.size(); ++i) {
        game.addPlayer(names[i].toStdString());
    }
    //game.manageGame();

    QString message = "Nombre de joueurs : " + QString::number(nbPlayers) +
                          "\nVariante : " + variante +
                          "\nNoms : " + names.join(", ");
    QMessageBox::information(this,"multi",message );
};
void MenuQt::OnSoloGameParameterReady(QString name, QString Variante, int level)
{
    GameQt& game = GameQt::giveInstance(2,Variante.toStdString());
    game.manageSoloGame(level);
    game.addPlayer(name.toStdString());
    QString message="Level: " + QString::number(level) +
                          "\nVariante : " + Variante +
                          "\nNoms : " + name;
    QMessageBox::information(this,"solo",message);

};


void MenuQt::boutonReprendreGameClique() {
    QString pseudo_game = QInputDialog::getText(this, "Game", "What was the pseudo of your game ?");
    string game_name = pseudo_game.toStdString();
    Amalena::savemanager save_manager;
    Amalena::GameMemento* game_memento = save_manager.restore(game_name);
    //little security because instance is unique
    GameQt::freeInstance();
    GameQt& game = GameQt::giveInstance(*game_memento);
    game.manageResumeGame();
    //game.endGame();
    GameQt::freeInstance();
}
