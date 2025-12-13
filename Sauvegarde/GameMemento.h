//
// Created by GAUTIER--BONNEAU on 05/12/2025.
//

#ifndef TESTSAUVEGARDE_GAMEMEMENTO_H
#define TESTSAUVEGARDE_GAMEMEMENTO_H
//
// Created by GAUTIER--BONNEAU on 04/12/2025.
//


#include <vector>
#include <string>
#include<map>
#include <nlohmann/json.hpp>
#include <unordered_map>
using json = nlohmann::json;
using namespace std;
namespace Amalena

    {
        class GameMemento
        {
            string game_id;
            string version;
            vector<int> riverid;
            vector<int> pileid;
            //Deck=> reconstruction possible à partir des paramètres
            vector<string> PlayersName;
            vector<int> PlayersStone;
            json boards;
            //avec le premier int Idtil id cell, position autant de map que de joueurs
            size_t nbplayer;//= taille devecor player
            size_t currentplayer;
            string variante;
//_______________________Getters and setters____________________________________________________
        public :
            string get_version() const {
                return version;
            }
            void set_version(const string& version) {
                this->version = version;
            }
            vector<int> get_riverid() const;
            void set_riverid(const vector<int>& riverid);
            vector<int> get_pileid() const;
            void set_pileid(const vector<int>& pileid);
            vector<string> get_players_name() const;
            void set_players_name(const vector<string>& players_name);
            vector<int> get_players_stone() const;
            void set_players_stone(const vector<int>& players_stone);
            json get_boards() const;
            void set_boards(json boards);
            size_t get_nbplayer() const;
            void set_nbplayer(const size_t nbplayer);
            size_t get_currentplayer() const;
            void set_currentplayer(const size_t currentplayer);
            string get_variante() const;
            void set_variante(const string& game_id);
            string get_game_id() const {
                return game_id;
            }
            void set_game_id(const string& game_id) {
                this->game_id = game_id;
            }
//___________________________________________________________________________________________________________________
        private :
            friend class Game;
            friend class savemanager;

        public:

            GameMemento(
            string game_id,
            string version,
            vector<int> riverid,
            vector<int> pileid,
            vector<string> PlayersName,
            vector<int> PlayersStone,
            json boards,
            size_t nbplayer,
            size_t currentplayer,
            string variante):game_id(game_id),version(version),riverid(riverid),pileid(pileid),PlayersName(PlayersName),PlayersStone(PlayersStone),
            boards(boards),nbplayer(nbplayer),currentplayer(currentplayer),variante(variante){};
            GameMemento();
            ~GameMemento()=default;
        };
    };

#endif //TESTSAUVEGARDE_GAMEMEMENTO_H