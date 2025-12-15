//
// Created by GAUTIER--BONNEAU on 22/11/2025
#include "savemanager.h"
#include <fstream>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;


namespace Amalena
{

    json savemanager::tojson()
    {
        json j;
        j["version"]=gameMemento->get_version();
        j["game_id"]=gameMemento->get_game_id();
        j["riverid"]=gameMemento->get_riverid();
        j["pileid"]=gameMemento->get_pileid();
        j["playersName"]=gameMemento->get_players_name();
        j["playerStone"]=gameMemento->get_players_stone();
        j["boards"] = gameMemento->get_boards();
        j["nbplayer"]=gameMemento->get_nbplayer();
        j["currentplayer"]=gameMemento->get_currentplayer();
        j["variante"]=gameMemento->get_variante();
        return j;

    }

    void savemanager::fromjson(json data)
    {
        gameMemento = new GameMemento(
        data["game_id"],
        data["version"],
        data["riverid"].get<std::vector<int>>(),
        data["pileid"].get<std::vector<int>>(),
        data["playersName"].get<std::vector<string>>(),
        data["playerStone"].get<std::vector<int>>(),
        data["boards"],
        data["nbplayer"],
        data["currentplayer"],
        data["variante"]
        );
    }

    void savemanager::save()
    {
        json newGame = tojson();
        json data;
        std::ifstream in("../sauvegarde.json");
        if (in.is_open()) {
            try {
                in >> data;
            } catch (...) {
                data = json::object();
            }
            in.close();
        }
        if (!data.contains("games") || !data["games"].is_array()) {
            data["games"] = json::array();
        }
        bool replaced = false;
        for (auto& game : data["games"]) {
            if (game.contains("game_id") &&
                game["game_id"] == newGame["game_id"]) {
                game = newGame;
                replaced = true;
                break;
            }
        }
        if (!replaced) {
            data["games"].push_back(newGame);
        }
        std::ofstream out("../sauvegarde.json");
        if (!out.is_open()) {
            std::cerr << "Failed to open save file for writing" << std::endl;
            return;
        }
        out << std::setw(4) << data << std::endl;
    }

    GameMemento* savemanager::restore(string id)
    {
        ifstream file("../sauvegarde.json");
        if (!file.is_open()) {
            cout << "Failed to open file" << endl;
            return nullptr;
        }
        json data;
        try {
            file >> data;
        } catch (const nlohmann::json::exception& e) {
            cout << "JSON parse error: " << e.what();
            return nullptr;
        }
        if (!data.contains("games") || !data["games"].is_array()) {
            cout << "Invalid save file: 'games' missing or not an array";
            return nullptr;
        }
        for (const auto& game : data["games"]) {
            if (!game.contains("game_id")) continue;
            if (game["game_id"].get<std::string>() == id) {
                fromjson(game);
                return gameMemento;
            }
        }
        cout << "Game with id '" << id << "' not found";
        return nullptr;
    }
}