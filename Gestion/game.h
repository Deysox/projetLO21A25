#ifndef PROJETLO21A25_PARTIE_H
#define PROJETLO21A25_PARTIE_H
using namespace std;

class Partie {
private:
	//tableau dynamique de joueurs
	//la partie gère le cycle de vie des joueurs
	Joueur** joueurs = nullptr;
	size_t nb_joueurs;
	size_t nb_joueurs_max;
	//la partie gère le cycle de vie des manches
	Manche** manches = nullptr;
	size_t manche_en_cours;
	size_t nb_manches;
	//parametres qui viennent du Menu
	size_t nombre_tuiles;
	string variante;
	string mode;
	string difficulte;
	Partie();
	~Partie();
	Partie(const Partie& c);
	Partie & = operator(const Partie & c);
	static Partie* instance;
public:
	void abandonnerPartie();
	void informationsPartie();
	void mancheSuivante();
	static Partie& donneInstance() {
		if (instance == nullptr) {
			instance = new Jeu;
			return *instance;
		}
	}
	static void libereInstance() {
		delete instance;
		instance = nullptr;
	}
};

#endif //PROJETLO21A25_PARTIE_H