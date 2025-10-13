#ifndef PROJETLO21A25_PLACEMENT_H
#define PROJETLO21A25_PLACEMENT_H

#include <map>
#include <vector>
#include <string>

#include "../Utilitaires/position.h"
#include "../Utilitaires/rotation.h"
#include "plateau.h"
using namespace std;

// ===== A supprimer après =====
namespace Marilou {
    enum class Couleur{};
    class Case;
    class Tuile;
}
// =====

namespace Barnabe {
    using namespace Marilou;

    class Placement {
        Plateau* plateau;
    public:
        Placeur(const Plateau* p);

        bool peutPlacer(const Tuile&, Position, Rotation);
        void placer(const Tuile&, Position, Rotation);
    };
}

#endif //PROJETLO21A25_PLACEMENT_H