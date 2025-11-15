//
// Created by elobo on 15/11/2025.
//

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;


void lecture_fichier() {
    ifstream fichier("tiles.json");
    if (fichier.is_open()){
        json data;
        fichier >> data;
        fichier.close();
        for (const auto& tile : data) {
            cout << "id : " << tile["id"] << endl;
        }
    } else {
        cout << "Erreur : Impossible de lire le fichier." << endl;
    }
}
