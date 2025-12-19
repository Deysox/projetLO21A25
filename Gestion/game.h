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
	/**
	 * Classe abstraite
	 * Classe qui régit le fonctionnement d'une partie
	 * Design pattern template method
	 */
	class Game {
	protected:
		/**
		 * Vecteur de joueurs
		 */
		vector<Player*> players;
		/**
		 * Joueur actuel, entier qui représente un indice du tableau
		 */
		size_t current_player = 0;
		/**
		 * Nombre de joueurs de la partie
		 */
		size_t nb_players;
		/**
		 * Attribut static qui représente le nombre maximal de joueurs pour une partie
		 */
		static size_t nb_players_max;
		/**
		 * Pointeur sur un deck, créé par le constructeur de Game
		 */
		Deck* deck = nullptr;
		/**
		 * Pointeur sur une pile, créée par le constructeur de Game
		 */
		Amalena::Pile* pile = nullptr;
		/**
		 * Pointeur sur la rivière, créée par le constructeur de Game
		 */
		Amalena::River* river = nullptr;
		/**
		 * Chaine de caractère pour la variante
		 */
		string variant = "";

		bool isSolo = false;
		int difficulty = 0;
		/**
		 * Premier constructeur de Game pour la création d'une nouvelle partie
		 * @param nb_players le nombre de joueurs
		 * @param variant la ou les variantes
		 */
		Game(size_t nb_players, string variant);
		/**
		 * Deuxième constructeur de Game pour le lancement d'une partie interrompue
		 * @param game_memento le game memento avec toutes les informations de la partie
		 */
		Game(const Amalena::GameMemento& game_memento);
		/**
		 * Destructeur virtuel pour l'héritage
		 */
		virtual ~Game();

		/**
		 * On delete le constructeur de recopie
		 * @param c une autre partie
		 */
		Game(const Game& c) = delete;

		/**
		 * Operateur d'affectation interdit
		 * @param c une autre partie
		 * @return reference vers game
		 */
		Game& operator=(const Game& c) = delete;
	public:
		/**
		 * Setter de la variante
		 * @param v variante
		 */
		void setVariant(const string& v) {
			variant = v;
		}

		/**
		 * Getter de la variante
		 * @return une reference constante vers la variante
		 */
		const string& getVariant() const {
			return variant;
		}
		void setSolo(const bool solo) {
			isSolo = solo;
		}
		const bool& isGameSolo() const {
			return isSolo;
		}
		void setDifficulty(const int dif)
		{
			difficulty = dif;
		}
		const int& getDifficulty() const
		{
			return difficulty;
		}

		/**
		 * Getter du nombre de joueurs
		 * @return le nombre de joueurs
		 */
		const size_t& getNbPlayers() const {
			return nb_players;
		}

		/**
		 * Getter du nombre de joueurs max
		 * @return le nombre de joueurs max
		 */
		static const size_t& getNbPlayersMax() {
			return nb_players_max;
		}

		/**
		 * Getter du joueur courant
		 * @return l'indice du joueur courant
		 */
		const size_t& getCurrentPlayer() const {
			return current_player;
		}

		/**
		 * Méthode virtuelle pure pour ajouter un joueur
		 * @param name of the player
		 */
		virtual void addPlayer(const string& name) = 0;

		/**
		 * Getter d'un joueur à partir d'une certaine position dans le tableau
		 * @param position
		 * @return
		 */
		Player* getPlayer(size_t position);
		void displayPlayers();
		void nextPlayer();
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
		Tile& pickRiver() {
			displayRiver();
			Tile& chosen_tile = chooseTileRiver();
			return chosen_tile;
		};
		virtual Tile& chooseTileRiver() = 0;
		virtual void displayRiver() = 0;
		void endGame() ;
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