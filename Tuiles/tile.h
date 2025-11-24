#ifndef PROJETLO21A25_TUILE_H
#define PROJETLO21A25_TUILE_H
#include <array>
#include <vector>
#include "cell.h"

using namespace std;

namespace Marilou {

	class Tile{
	public:
		Tile();
		~Tile();
		Tile(const Tile& p)=delete;
		Tile& operator=(Tile& p)=delete;
	};

	class StartingTile : public Tile {
		array <Marilou::Cell*, 4> cells;

		public :
			StartingTile(const array<Marilou::Cell*, 4>& c) : cells(c) {}
	};

	class ClassicTile : public Tile {
		array <Marilou::Cell*, 3> cells;

		public :
			ClassicTile(const array<Marilou::Cell*, 3>& c) : cells(c) {}
	};

	class AthenaTile : public Tile{
		Marilou::BicolorCell cell;

		public :
			AthenaTile(Marilou::BicolorCell c) : cell(c) {}
	};
}


namespace Barnabe {

	class Tile{
	protected:
		std::vector<const Cell*>* cells;

	public:
		Tile() : cells(new std::vector<const Cell*>()) {}
		~Tile();
		Tile(const Tile& p)=delete;
		Tile& operator=(Tile& p)=delete;

		unsigned int getSize() const {return cells->size();};
		const std::vector<const Cell*>* getCells() const {return cells;}
		virtual std::vector<Position> calculatePositions(Position p, Rotation r) const = 0;


	};

	class StartingTile : public Tile {
	public :
		StartingTile();
		virtual std::vector<Position> calculatePositions(Position p, Rotation r) const;

	};

	class ClassicTile : public Tile {
	public :
		ClassicTile(Color c1, Type t1, Color c2, Type t2, Color c3, Type t3);
		std::vector<Position> calculatePositions(Position p, Rotation r) const;
	};

	class AthenaTile : public Tile {
	BicolorCell* cell;

	public :
		AthenaTile(Color c1, Color c2, Type t);
		std::vector<Position> calculatePositions(Position p, Rotation r) const;
	};
}


#endif //PROJETLO21A25_TUILE_H