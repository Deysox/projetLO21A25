#ifndef PROJETLO21A25_TUILE_H
#define PROJETLO21A25_TUILE_H
#include <array>

using namespace std;

namespace Marilou {
	class Tile{
		Tile();
		~Tile();
		Tile(const Tile& p)=delete;
		Tile& operator=(Tile& p)=delete;
	};

	class StartingTile : public Tile {
		array <Marilou::Cell*, 4> cells;

		public :
			StartingTile(const array<Marilou::Cell*, 4>& c) : cells(c) {}
	}

	class ClassicTile : public Tile {
		array <Marilou::Cell*, 3> cells;

		public :
			ClassicTile(const array<Marilou::Cell*, 3>& c) : cells(c) {}
	}

	class AthenaTile : public Tile{
		Marilou::BicolorCell cell;

		public :
			AthenaTile(Marilou::BicolorCell c) : cell(c) {}
	}
}

#endif //PROJETLO21A25_TUILE_H