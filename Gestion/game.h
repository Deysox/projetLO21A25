#ifndef PROJETLO21A25_Game_H
#define PROJETLO21A25_Game_H
#include <string>
#include "../Chantier/river.h"
#include "../Joueurs/player.h"
#include "../Chantier/pile.h"
#include <vector>
#include "../Tuiles/deck.h"
#include "../Gestion/game.h"
#include "../Sauvegarde/savemanager.h"
#include "../Sauvegarde/GameMemento.h"
#include "../Joueurs/playerConsole.h"
#include "../Joueurs/playerQt.h"
#include "../Plateau/board.h"

using namespace Barnabe;
using namespace std;
namespace Eloise {
	class Game {
	protected:
		//game handles lifecycle of players
		vector<Player*> players;
		size_t current_player = 0;
		size_t nb_players;
		//default value
		static size_t nb_players_max;

		//game handles deck
		Eloise::Deck* deck = nullptr;

		//game handles pile, pile created when game starts
		Amalena::Pile* pile = nullptr;

		//game handles river, river created when game starts
		Amalena::River* river = nullptr;

		//game has potentially a variant
		string variant = "";

		//constructor for new game
		Game(size_t nb_players, string variant);

		//constructor for old game
		Game(const Amalena::GameMemento& game_memento);

		virtual ~Game();

		//singleton so delete
		Game(const Game& c) = delete;
		Game& operator=(const Game& c) = delete;
	public:
		//getters et setters
		void setVariant(const string& v) {
			variant = v;
		}
		const string& getVariant() const {
			return variant;
		}
		const size_t& getNbPlayers() const {
			return nb_players;
		}
		static const size_t& getNbPlayersMax() {
			return nb_players_max;
		}

		const size_t& getCurrentPlayer() const {
			return current_player;
		}
		//display and access player
		virtual void addPlayer(const string& name) = 0;

		Player* getPlayer(size_t position);

		//display players
		void displayPlayers();

		//set next player and architect so that the game continues
		void nextPlayer();

		//main method of the game
		void manageGame() {
			bool ok = true;
			addEachPlayerToGame();
			while (!(river->stay1() && pile->isEmpty())) {
				displayCurrentPlayerInfo();
				Amalena::River* river_copy = new Amalena::River(*river);
				BoardManager* board_copy = new BoardManager(players.at(current_player)->getBoard());
				ok = actionsPlayer(river_copy,board_copy);
				delete river_copy;
				delete board_copy;
				if (ok) {
					nextPlayer();
				}
				else {
					return;
				}
			}
		}

		virtual void addEachPlayerToGame() = 0;
		virtual void displayCurrentPlayerInfo() = 0;
		virtual bool actionsPlayer(Amalena::River* river_copy,BoardManager* board_copy) = 0;

		//main method if solo game
		virtual void manageSoloGame(int difficulty) {
			bool ok = true;
			askNameSoloGame();
			architectCreation(difficulty);

			while (!(river->stay1() && pile->isEmpty())) {
				if (current_player != 0){
					architectPlaySoloGame();
					nextPlayer();
				}
				else {
					BoardManager* board_copy = new BoardManager(players.at(0)->getBoard());
					Amalena::River* river_copy = new Amalena::River(*river);
					ok = realPlayerPlaySoloGame(board_copy,river_copy);
					delete river_copy;
					delete board_copy;
					if (ok) nextPlayer();
					else return;
				}
			}
		}

		virtual void askNameSoloGame() = 0;
		virtual void architectCreation(int difficulty) = 0;
		virtual void architectPlaySoloGame() = 0;
		virtual bool realPlayerPlaySoloGame(BoardManager* board_copy,Amalena::River* river_copy) = 0;

		//design pattern : template method
		Tile& pickRiver() {
			displayRiver();
			Tile& chosen_tile = chooseTileRiver();
			return chosen_tile;
		};

		virtual Tile& chooseTileRiver() = 0;
		virtual void displayRiver() = 0;

		//display scores at the end of the game
		void endGame() ;

		//quit and register game
		void abandonGame() {
			string version = " ";
			PlayerConsole* pC = dynamic_cast<PlayerConsole*>(players.at(0));
			if (pC) version = "console";
			else version = "qt";
			vector<int> riverid;
			for (auto it=river->begin(); it!=river->end(); ++it) {
				riverid.push_back((*it).getCell(0)->getID());
			}
			vector<int> pileid;
			for (auto it=pile->begin(); it!=pile->end(); ++it) {
				pileid.push_back((*it).getCell(0)->getID());
			}
			vector<string> PlayersName;
			vector<int> PlayersStone;
			json json_boards;
			size_t num_board = 0;
			for (auto it : players) {
				PlayersName.push_back(it->getName());
				PlayersStone.push_back(it->getStones());
				const Board& board = *(it->getBoard().getBoard());
				json json_board = board.toJsonBoard();
				json_boards[std::to_string(num_board)] = json_board;
				++num_board;
			}
			size_t nbplayer = nb_players;
			size_t currentplayer = current_player;
			string variante = variant;
			string id = displayAbandonGame1();
			Amalena::GameMemento game_memento(id,version, riverid,
						pileid,
						PlayersName,
						PlayersStone,
						json_boards,
						nbplayer,
						currentplayer,
						variante);
			Amalena::savemanager save_manager(&game_memento);
			save_manager.save();
			displayAbandonGame2();
		}

		virtual string displayAbandonGame1() = 0;
		virtual void displayAbandonGame2() = 0;

		void manageResumeGame() {
			bool ok = true;
			while (!(river->stay1() && pile->isEmpty())) {
				displayCurrentPlayerInfo();
				Amalena::River* river_copy = new Amalena::River(*river);
				BoardManager* board_copy = new BoardManager(players.at(current_player)->getBoard());
				ok = actionsPlayer(river_copy,board_copy);
				delete river_copy;
				delete board_copy;
				if (ok) nextPlayer();
				else return;
			}
		}
	};
}
#endif //PROJETLO21A25_Game_H