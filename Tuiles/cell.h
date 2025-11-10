#ifndef PROJETLO21A25_CASE_H
#define PROJETLO21A25_CASE_H

using namespace std;

namespace Marilou {
	enum class Color { BLUE, YELLOW, RED, PURPLE, GREEN, GREY}
	enum class Type { DISTRICT, PLACE, QUARRY }

	class Cell{
		Tile tile;
		Color color;
		Type type;
		~Cell();
		Cell(const Cell& p)=delete;
		Cell& operator=(Cell& p)=delete;
		public :
			Cell(Tile tile, Color c, Type t): tile(tile), color(c), Type(t) {};
			Color getColor() const { return color; }
			Type getType() const { return type; }
			Tile getTile() const { return tile; }
	};

	class BicolorCell : public Cell{
		Color secondaryColor;
		int rotation;
		~BicolorCell();
		BicolorCell(const BicolorCell& p)=delete;
		BicolorCell& operator=(BicolorCell& p)=delete;
		public :
			BicolorCell(Tile tile, Color c, Type t, Color sC, int r): Cell(tile,c,t), secondaryColor(sc), rotation(r) {};
			Color getSecondaryColor() const { return secondaryColor; }
			int getRotation() const { return rotation; }
	}
}

#endif //PROJETLO21A25_CASE_H