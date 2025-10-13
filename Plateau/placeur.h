//
// Created by barnab on 13/10/2025.
//

#ifndef PROJETLO21A25_PLACEUR_H
#define PROJETLO21A25_PLACEUR_H

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

    class Placeur {
        Plateau* plateau;
    public:
        Placeur(const Plateau* p);

        bool peutPlacer(const Tuile&, Position, Rotation);
        void placer(const Tuile&, Position, Rotation);
    };
}

#endif //PROJETLO21A25_PLACEUR_H