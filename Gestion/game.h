#ifndef PROJETLO21A25_Game_H
#define PROJETLO21A25_Game_H
#include <string>
#include "../Chantier/river.h"
#include "../Joueur/player.h"
#include "../Chantier/pile.h"
#include <vector>
#include "../Tuiles/deck.h"

using namespace std;

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

	//constructeur normal
	Game(size_t nb_players);
	//rajouter un constructeur à partir des fichiers json pour reprendre les parties

	//destructeur s'occupe d'aller stocker et sauvegarder les paramètres de la partie abandonnée dans un fichier json
	virtual ~Game();

	//singleton so delete
	Game(const Game& c) = delete;
	Game& operator=(const Game& c) = delete;
public:
	//getters et setters
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
	    addEachPlayerToGame();
	    while (!(river->stay1() && pile->isEmpty())) {
	        displayCurrentPlayerInfo();
	        Amalena::River* river_copy = new Amalena::River(*river);
	        BoardManager* board_copy = new BoardManager(players.at(current_player)->getBoard());
	    	actionsPlayer(river_copy,board_copy);
	    	delete river_copy;
	    	delete board_copy;
	        nextPlayer();
	    }
	}

	virtual void addEachPlayerToGame() = 0;
	virtual void displayCurrentPlayerInfo() = 0;
	virtual void actionsPlayer(Amalena::River* river_copy,BoardManager* board_copy) = 0;

	//main method if solo game
	virtual void manageSoloGame(int difficulty) {
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
	            realPlayerPlaySoloGame(board_copy,river_copy);
	            delete river_copy;
	            delete board_copy;
	            nextPlayer();
	        }
	    }
	}

	virtual void askNameSoloGame() = 0;
	virtual void architectCreation(int difficulty) = 0;
	virtual void architectPlaySoloGame() = 0;
	virtual void realPlayerPlaySoloGame(BoardManager* board_copy,Amalena::River* river_copy) = 0;

	//quit and register the game
	void abandonGame();

	//design pattern : template method
	Tile& pickRiver() {
		displayRiver();
		Tile& chosen_tile = chooseTileRiver();
		return chosen_tile;
	};

	virtual Tile& chooseTileRiver() = 0;
	virtual void displayRiver() = 0;

	void endGame();
};
#endif //PROJETLO21A25_Game_H