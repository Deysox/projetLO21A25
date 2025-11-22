//
// Created by barnab on 17/11/2025.
//
#include "boardmanager.h"

namespace Barnabe {
    BoardManager::BoardManager() : board(new Board()) {
        // Ajouter une tuile de départ
    }

    BoardManager::BoardManager(const BoardManager &e) {
        board = new Board();
        *board = *(e.board);

    }

    BoardManager& BoardManager::operator=(const BoardManager& e) {
        board = new Board();
        *board = *(e.board);
    }

    BoardManager::~BoardManager() {
        delete board;
    }

    bool BoardManager::canPlace(const Tile *t, Position p, Rotation r) const {
        // === Si c'est une tuile à trois cases. ===
        Position p1 = p;
        Position p2 = p+r;
        Position p3 = p+(r+1);
        // Si la hauteur des trois emplacements est différente, la position est invalide.
        if (!(board->getHeight(p1) == board->getHeight(p2) && board->getHeight(p1) == board->getHeight(p3))) return false;
        if (board->getCell(p1)) {
            // Si p1 n'est pas nullptr et que p2 ou p3 est nullptr, la position est invalide
            if (!board->getCell(p2) || !board->getCell(p3)) return false;
            // Si les tuiles n'ont pas la même tuile mère, la position est invalide
            if (!(board->getCell(p1)->getTile() == board->getCell(p2)->getTile() && board->getCell(p2)->getTile() == board->getCell(p3)->getTile())) return false;
        } else {

            // Si l'une des deux autres tuiles n'est pas nullptr, on renvoie faux
            if (board->getCell(p2) || board->getCell(p3)) return false;
        }

        for (auto it = p1.begin(); it != p1.end(); it++) { // Voisins de p1
            if (board->getCell(*it)) return true;
        }
        for (auto it = p2.begin(); it != p2.end(); it++) { // Voisins de p2
            if (board->getCell(*it)) return true;
        }
        for (auto it = p3.begin(); it != p3.end(); it++) { // Voisins de p3
            if (board->getCell(*it)) return true;
        }

        return false;

        // === Si c'est une monotuile ===

    }


    void BoardManager::place(const Tile *t, Position p, Rotation r) {
        if (!canPlace(t,p,r)) throw;// Exception à changer
        // Placement ici (en attente du taf de Marilou)
    }






}