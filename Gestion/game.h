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
		 * @return un pointeur sur joueur
		 */
		Player* getPlayer(size_t position);

		/**
		 * Methode qui parcourt le vecteur de joueurs et qui les affiche 1 par 1
		 */
		void displayPlayers();

		/**
		 * Methode qui avance l'indice dans le tableau de vecteur
		 * Concrètement : incrémentation d'un entier modulo le nombre de joueurs
		 */
		void nextPlayer();

		/**
		 * Fonction principale
		 * Template methode car elle appelle des fonctions virtuelles pures
		 */
		void manageGame() {
			//booléen qui indique si on doit continuer à jouer ou arrêter la partie
			bool ok = true;
			//on ajoute tous les joueurs à la partie
			addEachPlayerToGame();
			while (!(river->stay1() && pile->isEmpty())) {
				displayCurrentPlayerInfo();
				//copies de la rivière et du plateau pour toujours en garder la version originale et pouvoir annuler
				Amalena::River* river_copy = new Amalena::River(*river);
				BoardManager* board_copy = new BoardManager(players.at(current_player)->getBoard());
				//le booléen se met à jour à chaque appel de actionsPlayer()
				ok = actionsPlayer(river_copy,board_copy);
				//on libère les copies
				delete river_copy;
				delete board_copy;
				//si le booléen est toujours à true on peut continuer et passer au joueur suivant
				if (ok) {
					nextPlayer();
				}
				else {
					return;
				}
			}
		}

		/**
		 * Méthode virtuelle pure pour ajouter tous les joueurs au début de la partie
		 */
		virtual void addEachPlayerToGame() = 0;
		/**
		 * Méthode qui affiche toutes les informations du joueur en cours
		 */
		virtual void displayCurrentPlayerInfo() = 0;

		/**
		 * Méthode qui permet au joueur de piocher, de placer sa tuile et éventuellement de se raviser
		 * @param river_copy pour avoir l'état original de la rivière
		 * @param board_copy pour avoir l'état original du plateau
		 * @return un booléen qui indique si on doit stopper la partie ou pas
		 */
		virtual bool actionsPlayer(Amalena::River* river_copy,BoardManager* board_copy) = 0;
		/**
		 * Fonction principale dans le cas d'une game solo (implique gestion de l'architecte)
		 * Template methode car elle appelle des fonctions virtuelles pures
		 * @param la difficulté pour le compte du score de l'architecte
		 */
		virtual void manageSoloGame(int difficulty) {
			//booléen qui se met à false dans le cas où on stop la partie
			bool ok = true;
			//on demande son nom au joueur et on le crée
			askNameSoloGame();
			//on crée l'architecte en prenant en compte la difficulté pour le score
			architectCreation(difficulty);
			//on a fini la partie quand on a plus de tuiles
			while (!(river->stay1() && pile->isEmpty())) {
				if (current_player != 0){
					//l'architecte fait son tour
					architectPlaySoloGame();
					//on passe au joueur suivant
					nextPlayer();
				}
				else {
					//deux copies pour conserver les versions originales de la rivière et du plateau
					BoardManager* board_copy = new BoardManager(players.at(0)->getBoard());
					Amalena::River* river_copy = new Amalena::River(*river);
					//le joueur fait son tour à partir des versions de rivière et plateau qu'il va modifier
					//ok se met à jour et devient false si le joueur décide d'arrêter
					ok = realPlayerPlaySoloGame(board_copy,river_copy);
					//on libère la mémoire des copies
					delete river_copy;
					delete board_copy;
					//si ok est toujours vrai on peut continuer et passer au joueur suivant
					if (ok) nextPlayer();
					else return;
				}
			}
		}

		/**
		 * Méthode virtuelle pure pour créer le joueur solo
		 */
		virtual void askNameSoloGame() = 0;

		/**
		 * Méthode virtuelle pure pour créer l'architecte
		 * @param difficulty
		 */
		virtual void architectCreation(int difficulty) = 0;

		/**
		 * Méthode virtuelle pure pour le tour de l'architecte
		 */
		virtual void architectPlaySoloGame() = 0;

		/**
		 * Méthode virtuelle pure pour le tour du joueur
		 * @param board_copy
		 * @param river_copy
		 * @return un booléen pour savoir si on continue la partie
		 */
		virtual bool realPlayerPlaySoloGame(BoardManager* board_copy,Amalena::River* river_copy) = 0;

		/**
		 * Template method (design pattern)
		 * Méthode qui permet de piocher dans la rivière
		 * @return référence sur tuile choisie
		 */
		Tile& pickRiver() {
			//affiche la rivière
			displayRiver();
			//choix et renvoie de la tuile
			Tile& chosen_tile = chooseTileRiver();
			return chosen_tile;
		};

		/**
		 * Méthode virtuelle pure pour choisir la tuile dans la rivière
		 * @return référence sur tuile choisie
		 */
		virtual Tile& chooseTileRiver() = 0;

		/**
		 * Méthode virtuelle pure pour afficher la rivière
		 */
		virtual void displayRiver() = 0;

		/**
		 * Méthode appelée à la fin de la partie pour afficher les scores
		 */
		void endGame() ;

		/**
		 * Méthode qui permet l'abandon temporaire de la partie
		 * Elle crée un game memento à partir des informations de la partie
		 * Ensuite elle crée un save manager pour la sauvegarde dans un fichier json
		 * L'idée c'est d'optimiser et de ne garder que les informations essentielles comme les id pour les tuiles
		 */
		void abandonGame() {
			string version = " ";
			//dynamic cast pour connaître la version dans laquelle on joue (console ou qt)
			PlayerConsole* pC = dynamic_cast<PlayerConsole*>(players.at(0));
			if (pC) version = "console";
			else version = "qt";
			//vector avec les id des tuiles de la rivière
			vector<int> riverid;
			for (auto it=river->begin(); it!=river->end(); ++it) {
				riverid.push_back((*it).getCell(0)->getID());
			}
			//vector avec les id des tuiles de la pile
			vector<int> pileid;
			for (auto it=pile->begin(); it!=pile->end(); ++it) {
				pileid.push_back((*it).getCell(0)->getID());
			}
			vector<string> PlayersName;
			vector<int> PlayersStone;
			//on conserve les plateaux directement au format json
			json json_boards;
			size_t num_board = 0;
			for (auto it : players) {
				//pour chaque joueur on conserve son nom, ses pierres et son plateau
				PlayersName.push_back(it->getName());
				PlayersStone.push_back(it->getStones());
				const Board& board = *(it->getBoard().getBoard());
				//conversion en json
				json json_board = board.toJsonBoard();
				//ajout au gros json avec tous les plateaux
				json_boards[to_string(num_board)] = json_board;
				++num_board;
			}
			size_t nbplayer = nb_players;
			size_t currentplayer = current_player;
			string variante = variant;
			string id = displayAbandonGame1();
			//creation du game memento
			Amalena::GameMemento game_memento(id,version, riverid,
						pileid,
						PlayersName,
						PlayersStone,
						json_boards,
						nbplayer,
						currentplayer,
						variante);
			//creation du save manager à partir du game memento
			Amalena::savemanager save_manager(&game_memento);
			//appel de la fonction pour sauvegarder
			save_manager.save();
			displayAbandonGame2();
		}

		/**
		 * Méthode qui permet de choisir un pseudo pour identifier la partie abandonnée
		 * @return le pseudo de la partie sauvegardée
		 */
		virtual string displayAbandonGame1() = 0;
		virtual void displayAbandonGame2() = 0;

		/**
		 * Fonction principale dans le cas d'une reprise de partie (pas besoin de créer des joueurs)
		 * Template methode car elle appelle des fonctions virtuelles pures
		 */
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