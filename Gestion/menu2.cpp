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
        cout << "Game parameters\n";
        cout << "Tile_count ? : ";
        size_t tile_count = 0;
        cin >> tile_count;
        cout << "Variant ? : ";
        string variant;
        cin >> variant;
        cout << "Mode ? : ";
        string mode;
        cin >> mode;
        cout << "Difficulty ? : ";
        string difficulty;
        cin >> difficulty;
        cout << "Number of players ? : ";
        size_t nb_players = 0;
        cin >> nb_players;
        //penser à vérifier nb_players
        Partie& partie = Partie::donneInstance(tile_count, variant, mode, difficulty, nb_players);
        //add players to game
        for (int i = 0; i < nb_players; i++) {
            cout << "Name ?";
            string name;
            cin >> name;
            partie.addPlayer(name);
        }
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
