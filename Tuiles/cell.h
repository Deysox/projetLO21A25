#ifndef PROJETLO21A25_CASE_H
#define PROJETLO21A25_CASE_H

using namespace std;

namespace Marilou {
	enum class Color { BLUE, YELLOW, RED, PURPLE, GREEN}

    class Cell{
		int hauteur;
        ~Cell();
        Cell(const Cell& p)=delete;
        Cell& operator=(Cell& p)=delete;
		Cell(int h): hauteur(h) {};
		public :
			int getHauteur() const { return hauteur; }
    };

	class DistrictCell : public Cell {
		Color color;
		public :
			DistrictCell(int h, Color c): Cell(h), color(c) {}
			Color getColor() const {return color; }
	};

	class PlaceCell : public Cell {
		Color color;
		public :
			PlaceCell(int h, Color c): Cell(h), color(c) {}
			Color getColor() const {return color; }
	};

	class StoneQuarryCell : public Cell {
		public :
			StoneQuarryCell(int h): Cell(h) {}
	}

}

#endif //PROJETLO21A25_CASE_H