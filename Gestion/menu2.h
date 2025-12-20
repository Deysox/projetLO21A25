#ifndef MENU2
#define MENU2
#include <iostream>


namespace Eloise {
	/**
	 * Classe Menu pour la version console
	 */
	class Menu {
	public:
		/**
		 * Constructeur qui appelle display()
		 */
		Menu();

		/**
		 * Fonction principale qui va afficher le menu, proposer les différentes options et boucler
		 * Elle appelle les différentes méthodes de Game
		 */
		void display();
		//~Menu();
	private:
	};
}

#endif
