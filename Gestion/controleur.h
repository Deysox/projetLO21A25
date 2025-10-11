#ifndef PROJETLO21A25_CONTROLEUR_H
#define PROJETLO21A25_CONTROLEUR_H

namespace controleur {
	class Controleur {
	private : 
		Menu menu;
		Partie partie;
		Pioche pioche;
		static Controleur* instance;
		Controleur();
		~Controleur();
		Controleur(const Controleur& c);
		Controleur & = operator(const Controleur & c);
	public:
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
}

#endif //PROJETLO21A25_MENU_H