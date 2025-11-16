#ifndef PROJETLO21A25_Game_H
#define PROJETLO21A25_Game_H

#include <string>
#include "river.h"
#include "player.h"
#include "pile.h"
#include <vector>

#include "deck.h"

using namespace std;

class Game {
private:
	//game handles lifecycle of players
	vector<Barnabe::Player*> players;
	size_t architect = 0;
	size_t current_player = 0;
	size_t nb_players;
	//default value
	static size_t nb_players_max;

	//game handles river, river created when game starts
	Amalena::River* river = nullptr;

	//game handles pile, pile created when game starts
	Amalena::Pile* pile = nullptr;

	//game handles deck
	Deck* deck = nullptr;

	//parameters from Menu
	size_t tile_count;
	string variant;
	string mode;
	string difficulty;

	Game(size_t tile_count, string variant, string mode, string difficulty, size_t nb_players);
	~Game();
	Game(const Game& c);
	Game& operator=(const Game& c);

	//game instance
	static Game* instance;
public:
	void informationsGame();
	static Game& giveInstance(size_t tile_count, string variant, string mode, string difficulty, size_t nb_players) {
		if (instance == nullptr) {
			instance = new Game(tile_count, variant, mode, difficulty, nb_players);
		}
		return *instance;
	}
	static void freeInstance() {
		delete instance;
		instance = nullptr;
	}

	//getters et setters
	const size_t& getNbPlayers() const {
		return nb_players;
	}
	void setNbPlayers(size_t i) {
		nb_players = i;
	}
	static const size_t& getNbPlayersMax() {
		return nb_players_max;
	}

	const size_t& getTileCount() const {
		return tile_count;
	}
	void setTileCount(size_t t) {
		tile_count = t;
	}
	const string& getVariant() const {
		return variant;
	}
	void setVariant(string s) {
		variant = s;
	}
	const string& getMode() const {
		return mode;
	}
	void setMode(string s) {
		mode = s;
	}
	const string& getDifficulty() const {
		return difficulty;
	}
	void setDifficulty(string d) {
		difficulty = d;
	}
	const size_t& getArchitect() const {
		return architect;
	}
	void setArchitect(size_t i) {
		architect = i;
	}

	const size_t& getCurrentPlayer() const {
		return current_player;
	}
	void setCurrentPlayer(size_t i) {
		current_player = i;
	}

	//display and access player
	void addPlayer(const string& name);
	Barnabe::Player* getPlayer(size_t position);

	//display players
	void displayPlayers();

	//set next player and architect so that the game continues
	void nextPlayer();
	void nextArchitect();

	//main method of the game
	void manageGame();

	//quit and register the game
	void abandonGame();

	//player picks a tile in the pile so that he can play
	void pickRiver();

	//fill the river thanks to the pile
	void fillRiver();
};

#endif //PROJETLO21A25_Game_H