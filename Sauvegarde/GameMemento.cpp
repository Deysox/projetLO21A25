//
// Created by GAUTIER--BONNEAU on 05/12/2025.
//
#include"GameMemento.h"
#include <vector>
#include <string>
#include<map>
#include <unordered_map>
 namespace Amalena
 {
     vector<int> GameMemento::get_riverid() const
     {
         return riverid;
     }

     void GameMemento::set_riverid(const vector<int>& riverid)
     {
         this->riverid = riverid;
     }

     vector<int> GameMemento::get_pileid() const
     {
         return pileid;
     }

     void GameMemento::set_pileid(const vector<int>& pileid)
     {
         this->pileid = pileid;
     }

     vector<string> GameMemento::get_players_name() const
     {
         return PlayersName;
     }

     void GameMemento::set_players_name(const vector<string>& players_name)
     {
         PlayersName = players_name;
     }

     vector<int> GameMemento::get_players_stone() const
     {
         return PlayersStone;
     }

     void GameMemento::set_players_stone(const vector<int>& players_stone)
     {
         PlayersStone = players_stone;
     }

     json GameMemento::get_boards() const
     {
         return boards;
     }

     void GameMemento::set_boards(json boards)
     {
         this->boards = boards;
     }

     size_t GameMemento::get_nbplayer() const
     {
         return nbplayer;
     }

     void GameMemento::set_nbplayer(const size_t nbplayer)
     {
         this->nbplayer = nbplayer;
     }

     size_t GameMemento::get_currentplayer() const
     {
         return currentplayer;
     }

     void GameMemento::set_currentplayer(const size_t currentplayer)
     {
         this->currentplayer = currentplayer;
     }

     string GameMemento::get_variante() const
     {
         return variante;
     }

     void GameMemento::set_variante(const string& variante)
     {
         this->variante = variante;
     }
 }