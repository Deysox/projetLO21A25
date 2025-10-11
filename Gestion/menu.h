#ifndef PROJETLO21A25_MENU_H
#define PROJETLO21A25_MENU_H

#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>

//fait avec chatGPT, à changer après avoir suivi le cours sur Qt

//classe Menu = fenêtre graphique avec des boutons et des slots

/*
    La classe Menu permet de :
    - lancer une partie ainsi qu'en saisir les options et paramètres
    - reprendre une partie
    - ajouter des joueurs
    - afficher les règles
*/

namespace menu {
    class Menu : public QWidget {
        Q_OBJECT

    public:
        Menu() {
            auto* jouer = new QPushButton("Jouer");
            auto* regles = new QPushButton("Règles");
            auto* ajouterJoueur = new QPushButton("Ajouter un joueur");

            auto* layout = new QVBoxLayout;
            layout->addWidget(jouer);
            layout->addWidget(regles);
            layout->addWidget(ajouterJoueur);
            setLayout(layout);

            connect(jouer, &QPushButton::clicked, []() {
                QMessageBox::information(nullptr, "Partie", "La partie commence !");
                });

            connect(regles, &QPushButton::clicked, []() {
                QMessageBox::information(nullptr, "Règles", "Voici les règles du jeu !");
                });

            connect(ajouterJoueur, &QPushButton::clicked, []() {
                QMessageBox::information(nullptr, "Joueur", "Un joueur a été ajouté !");
                });
        }
    };
}
#endif //PROJETLO21A25_MENU_H