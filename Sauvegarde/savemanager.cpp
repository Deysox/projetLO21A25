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
        j["riverid"]=gameMemento->get_riverid();
        j["pileid"]=gameMemento->get_pileid();
        j["playersName"]=gameMemento->get_players_name();
        j["playerStone"]=gameMemento->get_players_stone();
        //j["boards"]=gameMemento->get_boards();
        auto boards=gameMemento->get_boards();
        json j_boards;
        json j_boardi;
        for (int i=0;i<boards.size();i++ )
        {
            std::string name = std::to_string(i);

            for (auto board : boards[i]){
            string key = to_string(board.first.first)+","+to_string(board.first.second);
            j_boardi[key]={board.second.first,board.second.second};
            }
            j_boards[name] =j_boardi ;
            //j_boards.push_back("");

        }
        j["boards"]=j_boards;
        j["nbplayer"]=gameMemento->get_nbplayer();
        j["currentplayer"]=gameMemento->get_currentplayer();
        j["variante"]=gameMemento->get_variante();
        return j;

    }
    void savemanager::fromjson(json data)
    {

        gameMemento->set_riverid(data["riverid"].get<std::vector<int>>());
        gameMemento->set_pileid(data["pileid"].get<std::vector<int>>()) ;
        gameMemento->set_players_name(data["playersName"].get<std::vector<string>>());
        gameMemento->set_players_stone(data["playerStone"].get<std::vector<int>>());
        gameMemento->set_nbplayer(data["nbplayer"]);
        gameMemento->set_currentplayer(data["currentplayer"]);
        gameMemento->set_variante  ( data["variante"]);
        auto jboards= data["boards"];
        vector<map<pair<int, int>, pair<int, unsigned int>>> vboards={};

        //for (int i=0; i<jboards.size();i++ )
        for (auto& [boardKey, jsonboard] : jboards.items())

        {
            map<pair<int, int>, pair<int, unsigned int>> board={};

            for (auto [keyStr, valueArr] : jsonboard.items())//partie inspirant des propositions d'une IAg
            {
                // keyStr = "x,y"
                int x, y;
                sscanf(keyStr.c_str(), "%d,%d", &x, &y);

                // valueArr = [val1, val2]
                int v1 = valueArr[0].get<int>();
                unsigned int v2 = valueArr[1].get<unsigned int>();

                board[{x, y}] = {v1, v2};
            }

            vboards.push_back(board);

        }
        gameMemento->set_boards  ( vboards);

    }
    void savemanager::save(){
        //réfléchir créer new enregistrement
         json j= tojson();
        std::ofstream file("../test.json");
        if (!file.is_open()) {
            std::cerr << "Failed to open file for writing" << std::endl;

        }


        file << std::setw(4) << j << std::endl;

    }
    void savemanager::restore()
    {
        std::ifstream file("../test.json");
        if (!file.is_open()) {
            std::cerr << "Failed to open file" << std::endl;
        }
        json data;
        file >> data;
        fromjson(data);
        }

}