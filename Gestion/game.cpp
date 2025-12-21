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
#include "../Joueurs/score.h"

using json = nlohmann::json;

namespace Eloise {
    size_t Game::nb_players_max = 4;

    Game::Game(size_t nb_players,string v) :
        nb_players(nb_players),
        deck(new Deck(nb_players)),
        pile(new Amalena::Pile(*deck)),
        river(new Amalena::River(nb_players+2,*pile)),
        variant(v){}

    Game::Game(const Amalena::GameMemento& game_memento) :
        nb_players(game_memento.get_nbplayer()),
        current_player(game_memento.get_currentplayer()),
        variant(game_memento.get_variante()){
    	//différenciation des deux cas obligatoire
        if (nb_players == 1) {
            deck = new Deck(nb_players+1);
        }
        else {
            deck = new Deck(nb_players);
        }
        pile = new Amalena::Pile(*deck);
        if (nb_players== 1) river = new Amalena::River(nb_players+3,*pile);
        else river = new Amalena::River(nb_players+2,*pile);
    	//on vide pile et rivière pour pouvoir les remplir avec les bonnes tuiles
        pile->clearVectorPile();
        river->clearVectorRiver();
    	//ouverture du fichier avec les tuiles
        ifstream fichier("tiles_2.json");
        json data;
    	//parsing
        if (fichier.is_open()){
            data = json::parse(fichier);
            fichier.close();
        } else {
            throw FileException("Impossible d'ouvrir le fichier des tuiles");
        }
    	//ici on va créer les tuiles correspondant aux identifiants récupérés
    	//rivière
        vector<int> river_ids = game_memento.get_riverid();
        for (auto it=river_ids.begin(); it!=river_ids.end(); ++it) {
            for (const auto& tile : data) {
                if (tile["id"] == *it) {
                	//on récupère toutes couleurs et tous les types
                    string t1 = tile["cells"][0]["type"];
                    string t2 = tile["cells"][1]["type"];
                    string t3 = tile["cells"][2]["type"];
                    string c1 = tile["cells"][0]["color"];
                    string c2 = tile["cells"][1]["color"];
                    string c3 = tile["cells"][2]["color"];
                    ClassicTile* game_tile = new ClassicTile(
                    	//3 cellules pour créer la tuile
                        Eloise::Deck::stringToColor[c1],Eloise::Deck::stringToType[t1],
                        Eloise::Deck::stringToColor[c2],Eloise::Deck::stringToType[t2],
                        Eloise::Deck::stringToColor[c3],Eloise::Deck::stringToType[t3]
                    );
                	//ajout à la rivière
                    river->addTilesInRiver(game_tile);
                }
            }
        }
    	//pile
    	//même logique
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
        vector<string> player_names = game_memento.get_players_name();
        int j = 0;
        for (auto it=player_names.begin(); it!=player_names.end(); ++it) {
        	//en fonction de la version on crée des joueurs qt ou des joueurs console
            if (game_memento.get_version() == "console") {
                players.push_back(new PlayerConsole(*it));
            }
            else {
                players.push_back(new PlayerQt(*it));
            }
            j++;
        }
        vector<int> player_stones = game_memento.get_players_stone();
        int i = 0;
        for (auto it=player_stones.begin(); it!=player_stones.end(); ++it) {
            players.at(i)->setStones(*it);
            i++;
        }
    	//on récupère le json avec les plateaux
        json player_boards = game_memento.get_boards();
        size_t k = 0;
    	//boucle pour affecter à chaque joueur son plateau venant du json
        for (auto& [boardKey, j_board] : player_boards.items()) {
        	//sécurités
            boardKey;
            j_board.dump(4);
        	//boucle try catch par sécurité
            try {
            	//conversion du json en plateau
                Board board = Board::fromJsonBoard(j_board);
            	//construction du board manager
                BoardManager bm(board);
                auto& player = players.at(k);
            	//affectation du plateau
                player->setBoard(bm);
            } catch (const exception& e) {
                cout << "Erreur : " << e.what();
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
            throw InvalidPositionException();
            return nullptr;
        }
    }

    void Game::nextPlayer() {
        current_player++;
        current_player %= nb_players;
    }

    void Game::endGame() {
		using namespace Marilou;

		ScoreVariants variants{};
		variants.home = variant.find("home") != std::string::npos;
		variants.market = variant.find("market") != std::string::npos;
		variants.barrack = variant.find("barrack") != std::string::npos;
		variants.temple = variant.find("temple") != std::string::npos;
		variants.garden = variant.find("garden") != std::string::npos;

		static ScoreBleu scoreBleu;
		static ScoreJaune scoreJaune;
		static ScoreRouge scoreRouge;
		static ScoreViolet scoreViolet;
		static ScoreVert scoreVert;
		static ScorePierre scorePierre;

		ScoreGeneral<> scoreGen;
		scoreGen.addScore(&scoreBleu);
		scoreGen.addScore(&scoreJaune);
		scoreGen.addScore(&scoreRouge);
		scoreGen.addScore(&scoreViolet);
		scoreGen.addScore(&scoreVert);
		scoreGen.addScore(&scorePierre);

		std::cout << "\n===== End of game, scores =====\n";

		struct Result
		{
			Player *player;
			int score;
			int stones;
		};
		std::vector<Result> results;

		if (isSolo && nb_players == 2)
		{
			Player *joueur = players[0];
			Player *architecte = players[1];

			int scoreJoueur = scoreGen.compute(*joueur, variants);
			int stonesJoueur = joueur->getStones();
			results.push_back({joueur, scoreJoueur, stonesJoueur});
			std::cout << joueur->getName() << " : " << scoreJoueur << " (stones : " << stonesJoueur << ")\n";

			ArchitectDifficulty diff =
				(difficulty == 1) ? ArchitectDifficulty::HIPPODAMOS : (difficulty == 2) ? ArchitectDifficulty::METAGENES
																						: ArchitectDifficulty::CALLICRATES;

			ScoreArchitecte scoreArch(diff);
			int scoreArchitecte = scoreArch.compute(*architecte, variants);
			int stonesArchitecte = architecte->getStones();
			results.push_back({architecte, scoreArchitecte, stonesArchitecte});
			std::cout << architecte->getName() << " : " << scoreArchitecte
					  << " (stones : " << stonesArchitecte << ")\n";
		}
		else
		{
			for (size_t i = 0; i < nb_players; ++i)
			{
				Eloise::Player *p = players[i];
				int score = scoreGen.compute(*p, variants);
				int stones = p->getStones();
				results.push_back({p, score, stones});
				std::cout << p->getName() << " : " << score << " (stones : " << stones << ")\n";
			}
		}

		int bestScore = std::numeric_limits<int>::min();
		int bestStones = std::numeric_limits<int>::min();
		std::vector<Result *> winners;

		for (auto &r : results)
		{
			if (r.score > bestScore)
			{
				bestScore = r.score;
				bestStones = r.stones;
				winners.clear();
				winners.push_back(&r);
			}
			else if (r.score == bestScore)
			{
				if (r.stones > bestStones)
				{
					bestStones = r.stones;
					winners.clear();
					winners.push_back(&r);
				}
				else if (r.stones == bestStones)
				{
					winners.push_back(&r);
				}
			}
		}

		if (winners.size() == 1)
		{
			std::cout << "\n"<< winners[0]->player->getName() << " won !\n";
		}
		else
		{
			std::cout << "\nTie between : ";
			for (size_t i = 0; i < winners.size(); ++i)
			{
				if (i > 0)
					std::cout << ", ";
				std::cout << winners[i]->player->getName();
			}
			std::cout << "\n";
		}
	}
}