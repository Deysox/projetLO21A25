//
// Created by elobo on 15/11/2025.
//

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

using namespace std;
using json = nlohmann::json;

void read_file() {
    ifstream fichier("tiles.json");
    if (fichier.is_open()){
        json data;
        fichier >> data;
        fichier.close();
        int id = 0;
        string nb_joueurs = " ";
        int nb_joueurs_int = 0;
        string type1 = " ";
        string couleur1 = " ";
        string type2 = " ";
        string couleur2 = " ";
        string type3 = " ";
        string couleur3 = " ";
        for (const auto& tile : data) {
            id = tile["id"];
            nb_joueurs = tile["Nb Joueurs"];
            nb_joueurs_int = stoi(nb_joueurs);
            type1 = tile["Type 1"];
            type2 = tile["Type 2"];
            type3 = tile["Type 3"];
            couleur1 = tile["Couleur 1"];
            couleur2 = tile["Couleur 2"];
            couleur3 = tile["Couleur 3"];
            //ensuite recuperer ces infos pour creer les cases et les tuiles
        }
    } else {
        cout << "Erreur : Impossible de lire le fichier." << endl;
    }
}

/*int main() {
    read_file();
}*/