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

	//constructeur normal
	Game(size_t nb_players);
	//rajouter un constructeur à partir des fichiers json pour reprendre les parties

	//destructeur s'occupe d'aller stocker et sauvegarder les paramètres de la partie abandonnée dans un fichier json
	~Game();

	//singleton donc delete
	Game(const Game& c) = delete;
	Game& operator=(const Game& c) = delete;

	//game instance
	static Game* instance;
public:
	static Game& giveInstance(size_t nb_players) {
		if (instance == nullptr) {
			instance = new Game(nb_players);
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

	//main method if solo game
	void manageSoloGame(int difficulty);

	//quit and register the game
	void abandonGame();

	//player picks a tile in the pile so that he can play
	Tile& pickRiver();

	void endGame();
};
#endif //PROJETLO21A25_Game_H