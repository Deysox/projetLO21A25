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

/*
*abstract class
*/
namespace Eloise {
	class Game {
	protected:
		/*
		*game handles lifecycle of players
		*/
		vector<Player*> players;
		size_t current_player = 0;
		size_t nb_players;
		//default value
		static size_t nb_players_max;

		/*
		*game handles lifecycle of deck
		*/
		Eloise::Deck* deck = nullptr;

		/*
		*game handles lifecycle of pile
		*/
		Amalena::Pile* pile = nullptr;

		/*
		 *game handles river, river created when game starts
		 */
		Amalena::River* river = nullptr;

		/*
		 *game has potentially 1 or several variants
		 */
		string variant = "";

		/*
		 *constructor for a new game taking 2 parameters : the number of player and the variant(s)
		 */
		Game(size_t nb_players, string variant);

		/*
		 *constructor for a new game taking a game memento in parameter
		 */
		Game(const Amalena::GameMemento& game_memento);

		/*
		 *virtual destructor because of inheritance
		 */
		virtual ~Game();

		//singleton so delete those 2 methods
		Game(const Game& c) = delete;
		Game& operator=(const Game& c) = delete;
	public:
		/*
		 *setter for variant
		 */
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
		/*
		 *attribut which allows us to know who is playing
		 */
		const size_t& getCurrentPlayer() const {
			return current_player;
		}
		/*
		 *method implemented by gameConsole and gameQt
		 */
		virtual void addPlayer(const string& name) = 0;
		/*
		 *get a Player at a position
		 */
		Player* getPlayer(size_t position);
		void displayPlayers();
		/*
		 *set next player and architect so that the game continues
		 */
		void nextPlayer();
		/*
		*main method of the game
		*template method
		*/
		void manageGame() {
			//boolean if abandon of the game
			bool ok = true;
			//pure virtual method
			addEachPlayerToGame();
			while (!(river->stay1() && pile->isEmpty())) {
				displayCurrentPlayerInfo();
				Amalena::River* river_copy = new Amalena::River(*river);
				BoardManager* board_copy = new BoardManager(players.at(current_player)->getBoard());
				//if ok = false we leave the method
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

		/*
		 *methods implemented by gameConsole and gameQt
		 *template method design pattern
		 */
		virtual void addEachPlayerToGame() = 0;
		virtual void displayCurrentPlayerInfo() = 0;
		virtual bool actionsPlayer(Amalena::River* river_copy,BoardManager* board_copy) = 0;

		/*
		*main method if solo game
		*template method
		*/
		virtual void manageSoloGame(int difficulty) {
			//boolean if abandon of the game
			bool ok = true;
			askNameSoloGame();
			architectCreation(difficulty);

			while (!(river->stay1() && pile->isEmpty())) {
				//turn of the architect
				if (current_player != 0){
					architectPlaySoloGame();
					nextPlayer();
				}
				else {
					//same as manage game if not architect
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

		//virtual pure methods, template method design pattern
		virtual void askNameSoloGame() = 0;
		virtual void architectCreation(int difficulty) = 0;
		virtual void architectPlaySoloGame() = 0;
		virtual bool realPlayerPlaySoloGame(BoardManager* board_copy,Amalena::River* river_copy) = 0;

		/*
		 *design pattern = template method
		 *method that displays the river and allows to pick a tile
		 */
		Tile& pickRiver() {
			displayRiver();
			Tile& chosen_tile = chooseTileRiver();
			return chosen_tile;
		};

		virtual Tile& chooseTileRiver() = 0;
		virtual void displayRiver() = 0;

		/*
		 *display scores at the end of the game
		 */
		void endGame() ;

		/*
		 *method that allow to quit and register the game for another time
		 */
		void abandonGame() {
			string version = " ";
			//dynamic cast of Playerto acknowledge the version in which we play
			PlayerConsole* pC = dynamic_cast<PlayerConsole*>(players.at(0));
			if (pC) version = "console";
			else version = "qt";
			vector<int> riverid;
			//recovery of all the id of the tiles in the river
			for (auto it=river->begin(); it!=river->end(); ++it) {
				riverid.push_back((*it).getCell(0)->getID());
			}
			//recovery of all the id of the tiles in the river
			vector<int> pileid;
			for (auto it=pile->begin(); it!=pile->end(); ++it) {
				pileid.push_back((*it).getCell(0)->getID());
			}
			//vector to recover the names of the players
			vector<string> PlayersName;
			//vector to recover the stones of the players
			vector<int> PlayersStone;
			//we recover the boards with a json format
			json json_boards;
			size_t num_board = 0;
			for (auto it : players) {
				PlayersName.push_back(it->getName());
				PlayersStone.push_back(it->getStones());
				//we recover the board
				const Board& board = *(it->getBoard().getBoard());
				//conversion in json thanks to toJsonBoard method
				json json_board = board.toJsonBoard();
				//we add the json board to the big json w/ all the boards
				json_boards[std::to_string(num_board)] = json_board;
				++num_board;
			}
			//direct recovery for those 3 attributs
			size_t nbplayer = nb_players;
			size_t currentplayer = current_player;
			string variante = variant;
			//we recover the id which is the pseudo of the current game chosen by the player who chose to abandon
			string id = displayAbandonGame1();
			//creation of game memento
			Amalena::GameMemento game_memento(id,version, riverid,
						pileid,
						PlayersName,
						PlayersStone,
						json_boards,
						nbplayer,
						currentplayer,
						variante);
			//creation of save manager
			Amalena::savemanager save_manager(&game_memento);
			//we use the save() method to save the game
			save_manager.save();
			displayAbandonGame2();
		}

		//pure virtual methods
		virtual string displayAbandonGame1() = 0;
		virtual void displayAbandonGame2() = 0;

		void manageResumeGame() {
			//boolean if abandon of the game
			bool ok = true;
			//same logic as manageGame
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