#ifndef PROJETLO21A25_PLACEMENT_H
#define PROJETLO21A25_PLACEMENT_H

#include <map>
#include <vector>
#include <string>

#include "../Utilitaires/position.h"
#include "../Utilitaires/rotation.h"
#include "board.h"
using namespace std;

// ===== A supprimer après =====
namespace Marilou {
    class Tile;
}
// =====

namespace Barnabe {
    using namespace Marilou;

    class Placement {
        Board* board;
    public:
        Placement(const Board* p);

        bool canPlace(const Tile&, Position, Rotation);
        void place(const Tile&, Position, Rotation);
    };
}

#endif //PROJETLO21A25_PLACEMENT_H