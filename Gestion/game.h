#ifndef PROJETLO21A25_Game_H
#define PROJETLO21A25_Game_H

#include <string>
#include "../Chantier/river.h"
#include "../Joueurs/player.h"
#include "../Chantier/pile.h"
#include <vector>
#include "../Tuiles/deck.h"

using namespace std;

class Game {
private:
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

	//parameters from Menu
	size_t tile_count;
	/*string variant;
	string mode;
	string difficulty;*/

	//constructeur normal
	Game(size_t tile_count, string variant, string mode, string difficulty, size_t nb_players);
	//rajouter un constructeur à partir des fichiers json pour reprendre les parties

	//destructeur s'occupe d'aller stocker et sauvegarder les paramètres de la partie abandonnée dans un fichier json
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
	static const size_t& getNbPlayersMax() {
		return nb_players_max;
	}
	const size_t& getTileCount() const {
		return tile_count;
	}
	/*const string& getVariant() const {
		return variant;
	}
	const string& getMode() const {
		return mode;
	}
	const string& getDifficulty() const {
		return difficulty;
	}*/
	const size_t& getCurrentPlayer() const {
		return current_player;
	}
	//display and access player
	void addPlayer(const string& name);

	Player* getPlayer(size_t position);

	//display players
	void displayPlayers();

	//set next player and architect so that the game continues
	void nextPlayer();

	//main method of the game
	void manageGame();

	//quit and register the game
	void abandonGame();

	//player picks a tile in the pile so that he can play
	Tile& pickRiver();

	void endGame();
};
#endif //PROJETLO21A25_Game_H