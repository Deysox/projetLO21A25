#include "menu.h"
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
    boutonLancerPartie = new QPushButton("Lancer Partie");
    boutonReprendrePartie = new QPushButton("Reprendre Partie");
    boutonAfficherRegles = new QPushButton("Afficher regles");

    //Affichage
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(boutonLancerPartie);
    layout->addSpacing(15);
    layout->addWidget(boutonReprendrePartie);
    layout->addSpacing(15);
    layout->addWidget(boutonAfficherRegles);
    setLayout(layout);
    setWindowTitle("Menu du jeu");

    //Connexions
    connect(boutonAfficherRegles, &QPushButton::clicked,
        this, &Menu::boutonAfficherReglesClique);
    connect(boutonLancerPartie, &QPushButton::clicked,
        this, &Menu::boutonLancerPartieClique);
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

void Menu::boutonLancerPartieClique() {
    Partie& partie = Partie::donneInstance();
    partie.informationsPartie();
}
