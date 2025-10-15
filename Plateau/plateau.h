#ifndef PROJETLO21A25_PLATEAU_H
#define PROJETLO21A25_PLATEAU_H

#include <map>
#include <vector>
#include <string>

#include "../Utilitaires/position.h"
#include "../Utilitaires/rotation.h"
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

    class Plateau {
        map<Position, Case*> cases;
        Position coin_tl;
        Position coin_br;
    public:
        class const_case_iterator {
            const Case* current;
            Couleur col;
            friend class Plateau;
            const_case_iterator(Case* debut, Couleur c) : current(debut), col(c) {};
            const_case_iterator(Case* debut) : current(debut) {};
        public:
            const_case_iterator& operator++();
            const Case& operator*();
            bool operator !=(const_case_iterator& it);
        };

        // class neighbour_const_iterator {
        //     const Case* current;
        //     neighbour_const_iterator(const Case* c);
        // public:
        //     neighbour_const_iterator& operator++();
        //     const Case& operator*();
        //     bool operator != (neighbour_const_iterator&);
        // };

        Plateau() : coin_br(Position(0,0)), coin_tl(Position(0,0)) {};
        ~Plateau();
        Plateau(const Plateau&);

        Plateau& operator=(const Plateau&);

        const_case_iterator begin() const;
        const_case_iterator end() const;

        Case& getCase(Position pos) const;
        Case& getCase(int x, int y) const;

        Position findCase(const Case&);

        void setCase(Position pos, const Case& c);
        void setCase(int x, int y, const Case& c);

        void valide(const vector<Position>&) const;

        friend ostream& operator<<(ostream& f, const Plateau& p);

    };
}

ostream& operator<<(ostream& f, const Barnabe::Plateau& p);

#endif //PROJETLO21A25_PLATEAU_H