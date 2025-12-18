#ifndef MENU2
#define MENU2
#include <iostream>


namespace Eloise {
	class Menu {
	public:
		/*
		 *constructor that calls display() method
		 */
		Menu();
		void display();
		~Menu() = default;
	};
}

#endif
