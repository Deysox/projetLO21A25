#include <iostream>
#include "menu2.h"
#include "game.h"
using namespace std;

Menu::Menu() {
    afficher();
}

void Menu::afficher() {
    cout << "Bienvenue dans le menu de la partie\n"
        << "Que voulez-vous faire ?\n"
        << "1. Lancer une partie\n"
        << "2. Reprendre une partie\n"
        << "3. Afficher les regles" << std::endl;
    char choix = 'A';
    cin >> choix;
    switch (choix)
    {
        //erreurs sans les {} car besoin d'un "scope" local pour partie
    case '1': {
        cout << "Lancement de la partie.\n" << endl;
        Partie& partie = Partie::donneInstance();
        partie.informationsPartie();
        break;
    }
    case '2':
        cout << "Reprise de la partie.\n" << endl;
        break;
    case '3':
        cout << "Voici les regles du jeu :\n"
            "Dans ce jeu de pose de tuiles, les joueurs prennent le role d'architectes qui s'affrontent "
            "en creant chacun une cite a l'aide de tuiles cite. Chaque tuile cite est composee de 3 "
            "hexagones construction, chaque hexagone representant un quartier, une place ou une carriere. "
            "Il existe plusieurs types de quartier. Chaque quartier rapporte des points de victoire "
            "s'ils sont correctement places selon son type." << endl;
        break;
    default:
        cout << "Choix invalide.\n" << endl;
    }
}
