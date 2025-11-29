//
// Created by barnab on 17/11/2025.
//
#include "boardmanager.h"

namespace Barnabe {
    BoardManager::BoardManager() : board(new Board()) {
        startingTile = new StartingTile();
        place(startingTile,0,0, true);
    }

    BoardManager::BoardManager(const BoardManager &e) {
        board = new Board();
        *board = *(e.board);

    }

    BoardManager& BoardManager::operator=(const BoardManager& e) {
        board = new Board();
        *board = *(e.board);
        return *this;
    }

    BoardManager::~BoardManager() {
        delete board;
        delete startingTile;
    }

    bool BoardManager::canPlace(const ClassicTile *t, Position p, Rotation r, bool adjacentIgnore) const {
        const vector<const Cell*>* cells = t->getCells();
        vector<Position> positions = t->calculatePositions(p,r);

        Position initialPos = positions[0];
        const Cell* initialCell = board->getCell(initialPos);
        unsigned int initialHeight = board->getHeight(initialPos);

        if (initialCell) {
            bool sameTiletest = false;
            for (auto it = positions.begin(); it != positions.end(); it++ ) {
                if (board->getHeight(*it) != initialHeight) return false;
                if (board->getCell(*it)->getTile() != initialCell->getTile()) sameTiletest = true;
            }


        } else {
            for (auto it = positions.begin(); it != positions.end(); it++ ) {
                if (board->getCell(*it) != nullptr) return false;
            }
        }

        if (adjacentIgnore) {
            return true;
        }
        for (auto it = positions.begin(); it != positions.end(); it++ ) {
            for (auto it_pos = it->begin(); it_pos != it->end(); it_pos++) {
                if (board->getCell(*it_pos) != nullptr) return true;
            }
        }

        return false;
    }

    void BoardManager::place(const ClassicTile *t, Position p, Rotation r, bool adjacentIgnore) {
        if (!canPlace(t,p,r, adjacentIgnore)) throw;// Exception à changer
        const vector<const Cell*>* cells = t->getCells();
        vector<Position> positions = t->calculatePositions(p,r);

        unsigned int height = board->getHeight(positions[0])+1;

        int i = 0;
        for (auto it = cells->begin(); it != cells->end(); it++) {
            board->setCell(positions[i],height,*it);
            i++;
        }
    }

    ostream& operator<<(ostream& f, const BoardManager& c) {
        f << *(c.board);
        return f;
    }


}