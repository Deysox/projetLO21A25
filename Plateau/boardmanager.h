#ifndef PROJETLO21A25_PLACEMENT_H
#define PROJETLO21A25_PLACEMENT_H

#include <map>
#include <vector>
#include <string>

#include "../Utilitaires/position.h"
#include "../Utilitaires/rotation.h"
#include "board.h"
#include ""

using namespace std;


namespace Barnabe {
    using namespace Marilou;

    class BoardManager {
        Board* board;
    public:
        BoardManager();
        BoardManager(const BoardManager& e);
        ~BoardManager();

        BoardManager& operator=(const BoardManager& e);

        bool canPlace(const Tile&, Position, Rotation) const;
        void place(const Tile&, Position, Rotation);

        ostream& display(ostream& f, bool contour = false) const;

        int boardScore() const;
    };
}

ostream& operator<<(ostream& f, const Barnabe::BoardManager& c);

#endif //PROJETLO21A25_PLACEMENT_H