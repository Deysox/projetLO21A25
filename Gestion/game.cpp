//
// Created by elobo on 02/12/2025.
//
#include "game.h"
#include "../Chantier/river.h"
#include <iostream>
#include <vector>
#include "../Tuiles/deck.h"
#include "../Joueurs/player.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include "../Plateau/board.h"
#include "../Plateau/boardmanager.h"

using json = nlohmann::json;

//static attributs
size_t Game::nb_players_max = 4;

//constructor to launch a new game
Game::Game(size_t nb_players,string v) :
    nb_players(nb_players),
    deck(new Eloise::Deck(nb_players)),
    pile(new Amalena::Pile(*deck)),
    river(new Amalena::River(nb_players+2,*pile)),
    variant(v){}

//retrieve tiles' id
//constructor using game_memento
Game::Game(const Amalena::GameMemento& game_memento) :
    //we recover info from the game memento
    nb_players(game_memento.get_nbplayer()),
    current_player(game_memento.get_currentplayer()),
    variant(game_memento.get_variante()){
    //creation of the deck
    if (nb_players == 1) {
        deck = new Eloise::Deck(nb_players+1);
    }
    else {
        deck = new Eloise::Deck(nb_players);
    }
    //creation of the pile
    pile = new Amalena::Pile(*deck);
    if (nb_players== 1) river = new Amalena::River(nb_players+3,*pile);
    else river = new Amalena::River(nb_players+2,*pile);
    //we clear the pile and the river so that we can fill it with the right tiles
    pile->clearVectorPile();
    river->clearVectorRiver();
    //opening of the json
    ifstream fichier("../tiles_2.json");
    json data;
    if (fichier.is_open()){
        //parsing of file
        data = json::parse(fichier);
        fichier.close();
    } else {
        cout << "Error w/ file." << endl;
    }
    //recovery of the tiles of the river
    vector<int> river_ids = game_memento.get_riverid();
    for (auto it=river_ids.begin(); it!=river_ids.end(); ++it) {
        //then we search in the json the corresponding tile thanks to the id so that we can create the good tile
        for (const auto& tile : data) {
            //we compare the id
            if (tile["id"] == *it) {
                string t1 = tile["cells"][0]["type"];
                string t2 = tile["cells"][1]["type"];
                string t3 = tile["cells"][2]["type"];
                string c1 = tile["cells"][0]["color"];
                string c2 = tile["cells"][1]["color"];
                string c3 = tile["cells"][2]["color"];
                ClassicTile* game_tile = new ClassicTile(
                    Eloise::Deck::stringToColor[c1],Eloise::Deck::stringToType[t1],
                    Eloise::Deck::stringToColor[c2],Eloise::Deck::stringToType[t2],
                    Eloise::Deck::stringToColor[c3],Eloise::Deck::stringToType[t3]
                );
                //finally we add the tile created to the river
                river->addTilesInRiver(game_tile);
            }
        }
    }
    //same idea for the pile
    vector<int> pile_ids = game_memento.get_pileid();
    for (auto it=pile_ids.begin(); it!=pile_ids.end(); ++it) {
        for (const auto& tile : data) {
            if (tile["id"] == *it) {
                string t1 = tile["cells"][0]["type"];
                string t2 = tile["cells"][1]["type"];
                string t3 = tile["cells"][2]["type"];
                string c1 = tile["cells"][0]["color"];
                string c2 = tile["cells"][1]["color"];
                string c3 = tile["cells"][2]["color"];
                ClassicTile* game_tile = new ClassicTile(
                    Eloise::Deck::stringToColor[c1],Eloise::Deck::stringToType[t1],
                    Eloise::Deck::stringToColor[c2],Eloise::Deck::stringToType[t2],
                    Eloise::Deck::stringToColor[c3],Eloise::Deck::stringToType[t3]
                );
                pile->addTilesInPile(game_tile);
            }
        }
    }
    //we create the players : Qt or Console thanks to the attribute version
    vector<string> player_names = game_memento.get_players_name();
    int j = 0;
    for (auto it=player_names.begin(); it!=player_names.end(); ++it) {
         if (game_memento.get_version() == "console") {
             players.push_back(new PlayerConsole(*it));
         }
        else {
            players.push_back(new PlayerQt(*it));
        }
        j++;
    }
    //attribution of stones to each player
    vector<int> player_stones = game_memento.get_players_stone();
    int i = 0;
    for (auto it=player_stones.begin(); it!=player_stones.end(); ++it) {
        players.at(i)->setStones(*it);
        i++;
    }
    //recovery of the boards
    json player_boards = game_memento.get_boards();
    size_t k = 0;
    for (auto& [boardKey, j_board] : player_boards.items()) {
        //2 local variables needed, otherwise bugs
        boardKey;
        j_board.dump(4);
        try {
            //for each player we recover his board from the json
            //we create a board and a boardmanager that we affect to the player
            Board board = Board::fromJsonBoard(j_board);
            BoardManager bm(board);
            auto& player = players.at(k);
            player->setBoard(bm);
        } catch (const exception& e) {
            cout << "Exception caught: " << e.what() << endl;
        }
        ++k;
    }
}

Game::~Game(){
    for (auto& p: players) {
        delete p;
    }
    delete river;
    delete pile;
    delete deck;
}

void Game::displayPlayers() {
    for (auto player : players) {
        cout << player->getName() << "\n";
    }
}

Player* Game::getPlayer(size_t position) {
    if (position < nb_players) {
        return players.at(position);
    }
    else {
        cout << "Invalid position.";
        return nullptr;
    }
}

void Game::nextPlayer() {
    current_player++;
    current_player %= nb_players;
}

void Game::endGame() {
    //displaying of each player's score thanks to method of Player
}