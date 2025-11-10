#ifndef PROJETLO21A25_CASE_H
#define PROJETLO21A25_CASE_H

#include <iostream>
#include <map>

using namespace std;



namespace Marilou {
	enum class Color { BLUE, YELLOW, RED, PURPLE, GREEN, GREY};
	enum class Type { DISTRICT, PLACE, QUARRY };

	static std::map<Color, string> ansiColorCodes = {{Color::BLUE, "4"},{Color::RED, "1"},{Color::GREEN, "2"},{Color::YELLOW, "3"},{Color::GREY, "7"}, {Color::PURPLE, "5"}};
	static std::map<Color, string> akroColorCodes = {{Color::BLUE, "h"},{Color::RED, "c"},{Color::GREEN, "j"},{Color::YELLOW, "m"},{Color::GREY, "_"},{Color::PURPLE, "t"}};
	static std::map<Type, string> akroTypeCodes = {{Type::DISTRICT, "Q"},{Type::PLACE, "P"},{Type::QUARRY, "C"}};

	class Tile;

	class Cell{


		const Tile* tile;
		Color color;
		Type type;

	public:
		Cell(const Tile* tile, Color c, Type t): tile(tile), color(c), type(t) {}
		Cell(const Cell& c);
		Color getColor() const { return color; }
		Type getType() const { return type; }
		const Tile* getTile() const { return tile; }

		// Fonctions d'affichage, faites par Barnabé
		ostream& displayTop(ostream& f, unsigned int height) const;
		ostream& displayBottom(ostream& f) const;
	};

	class BicolorCell : public Cell{
		Color secondaryColor;
		int rotation;

	public :
		BicolorCell(const Tile* tile, Color c, Type t, Color sC, int r): Cell(tile,c,t), secondaryColor(sC), rotation(r) {};
		BicolorCell(const BicolorCell& c);
		~BicolorCell();
		Color getSecondaryColor() const { return secondaryColor; }
		int getRotation() const { return rotation; }
	};
}



#endif //PROJETLO21A25_CASE_H