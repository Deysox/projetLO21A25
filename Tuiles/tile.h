#ifndef PROJETLO21A25_TUILE_H
#define PROJETLO21A25_TUILE_H
#include <array>
#include "cell.h"

using namespace std;

namespace Marilou {
    class Tile{
        Tile();
        ~Tile();
        Tile(const Tile& p)=delete;
        Tile& operator=(Tile& p)=delete;
    };

	class StartingTile {
		array <Marilou::Cell*, 4> cells;

        public :
			StartingTile(const array<Marilou::Cell*, 4>& c) : cells(c) {}
	};

		class ClassicTile {
		array <Marilou::Cell*, 3> cells;

        public :
			ClassicTile(const array<Marilou::Cell*, 3>& c) : cells(c) {}
	};

		class AthenaTile {
		array <Marilou::Cell*, 2> cells;

        public :
			AthenaTile(const array<Marilou::Cell*, 2>& c) : cells(c) {}
	};
}

#endif //PROJETLO21A25_TUILE_H