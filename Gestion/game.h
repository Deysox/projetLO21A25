#ifndef PROJETLO21A25_PARTIE_H
#define PROJETLO21A25_PARTIE_H

#include <string>
#include "river.h"
#include "player.h"
#include <vector>

using namespace std;

class Partie {
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

	Partie();
	~Partie();
	Partie(const Partie& c);
	Partie& operator=(const Partie& c);

	//game instance
	static Partie* instance;
public:
	void abandonnerPartie();
	void informationsPartie();
	void mancheSuivante();
	static Partie& donneInstance() {
		if (instance == nullptr) {
			instance = new Partie();
			return *instance;
		}
	}
	static void libereInstance() {
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
	const string& setVariant() const {
		return variant;
	}
	void getVariant(string s) {
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

#endif //PROJETLO21A25_PARTIE_H