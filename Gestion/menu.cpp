/*#include "menu.h"
#include "game.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QString>
#include <QDialog>
#include <QLineEdit>
#include <QtGui>
#include <QMessageBox>
#include <Qobject>

Menu::Menu(QWidget* parent) : QWidget(parent) {
    //Boutons
    boutonLancerGame = new QPushButton("Lancer Game");
    boutonReprendreGame = new QPushButton("Reprendre Game");
    boutonAfficherRegles = new QPushButton("Afficher regles");

    //Affichage
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(boutonLancerGame);
    layout->addSpacing(15);
    layout->addWidget(boutonReprendreGame);
    layout->addSpacing(15);
    layout->addWidget(boutonAfficherRegles);
    setLayout(layout);
    setWindowTitle("Menu du jeu");

    //Connexions
    connect(boutonAfficherRegles, &QPushButton::clicked,
        this, &Menu::boutonAfficherReglesClique);
    connect(boutonLancerGame, &QPushButton::clicked,
        this, &Menu::boutonLancerGameClique);
}

//Slots
void Menu::boutonAfficherReglesClique() {
    QMessageBox::information(this,
        "Regles du jeu",
        "Dans ce jeu de pose de tuiles, les joueurs prennent le role d'architectes qui s'affrontent "
        "en creant chacun une cite a l'aide de tuiles cite. Chaque tuile cite est composee de 3 "
        "hexagones construction, chaque hexagone representant un quartier, une place ou une carriere. "
        "Il existe plusieurs types de quartier. Chaque quartier rapporte des points de victoire "
        "s'ils sont correctement places selon son type.");
}

void Menu::boutonLancerGameClique() {
    Game& Game = Game::donneInstance();
    Game.informationsGame();
}
*/