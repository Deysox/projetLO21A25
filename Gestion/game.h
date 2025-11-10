#ifndef PROJETLO21A25_Game_H
#define PROJETLO21A25_Game_H

#include <string>
#include "../Chantier/river.h"
#include "../Joueurs/player.h"
#include <vector>

using namespace std;

class Game {
private:
	//game handles lifecycle of players
	vector<Barnabe::Player*> players;
	Barnabe::Player* architect = nullptr;
	size_t nb_players;
	//default value
	size_t nb_players_max = 5;

	//game handles river, river created when game starts
	Amalena::River* river = nullptr;

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
	void abandonGame();
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
	const size_t& getNbPlayersMax() const {
		return nb_players_max;
	}
	void setNbPlayersMax(size_t i) {
		nb_players_max = i;
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
	Barnabe::Player* getArchitect() const {
		return architect;
	}
	void setArchitect(Barnabe::Player* p) {
		architect = p;
	}

	//ajouter et accéder à un joueur
	void addPlayer(const string& name);
	Barnabe::Player* getPlayer(size_t position);

	//afficher les joueurs
	void displayPlayers();
};

#endif //PROJETLO21A25_Game_H