#ifndef PROJETLO21A25_PLATEAU_H
#define PROJETLO21A25_PLATEAU_H

#include <map>
#include <vector>
#include <string>
#include <unordered_map>

#include "../Utilitaires/position.h"
#include "../Utilitaires/rotation.h"

#include "../Tuiles/cell.h"
using namespace std;

namespace Barnabe {


    class Board {
        map<Position, pair<const Marilou::Cell*, unsigned int>, PosCmp> cells;
        Position corner_tl;
        Position corner_br;
    public:


        Board();
        ~Board();
        Board(const Board&);

        Board& operator=(const Board&);

        std::pair<Position, Position> getCorners() const;

        const Marilou::Cell* getCell(Position pos) const;
        const Marilou::Cell* getCell(int x, int y) const;

        unsigned int getHeight(Position pos) const;
        unsigned int getHeight(int x, int y) const;

        //Position findCell(const Cell&) const;

        void setCell(Position pos, unsigned int h, const Marilou::Cell* c);
        void setCell(int x, int y, unsigned int h, const Marilou::Cell* c);

        //void validPos(const vector<Position>&) const;

        friend ostream& operator<<(ostream& f, const Board& b);

        // Itérateurs
        class iterator {
            friend class board;
            map<Position, pair<const Marilou::Cell*, unsigned int>, PosCmp>::iterator it;
            iterator(map<Position, pair<const Marilou::Cell*, unsigned int>, PosCmp>::iterator i) : it(i) {}
        public:
            iterator& operator++() {
                it++;
                return *this;
            }
            iterator operator++(int) {
                auto old = it;
                it++;
                return {old};
            }
            bool operator!=(const iterator& e) {
                return it != e.it;
            }
            bool operator==(const iterator& e) {
                return it == e.it;
            }
            pair<Position, pair<const Marilou::Cell*, unsigned int>> operator*() {
                return *it;
            }
        };




    };

    ostream& operator<<(ostream& f, const Barnabe::Board& b);
}



#endif //PROJETLO21A25_PLATEAU_H