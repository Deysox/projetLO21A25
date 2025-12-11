//
// Created by barnab on 17/11/2025.
//
#include "boardmanager.h"
#include "../Utilitaires/exceptions.h"

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
        if (&e != this) {
            board = new Board();
            *board = *(e.board);
        }
        return *this;
    }

    BoardManager::~BoardManager() {
        delete board;
        delete startingTile;
    }


    int BoardManager::place(const Tile *t, Position p, Rotation r, bool adjacentIgnore) {
        vector<Position> positions = t->calculatePositions(p,r); // Calcul des positions à vérifier
        // for (auto it = positions.begin(); it != positions.end(); it++) cout << it->x() << " " << it->y() << endl;

        int stoneCount = 0;

        Position initialPos = positions[0]; // Position initiale utilisée comme base de comparaison
        const Cell* initialCell = board->getCell(initialPos); // Cellule initiale
        unsigned int initialHeight = board->getHeight(initialPos); // Hauteur initiale


        if (initialCell) { // S'il y a déjà une cellule dans la position intiale
            int initialID = initialCell->getID();
            bool sameTiletest = false;
            for (auto it = positions.begin(); it != positions.end(); it++ ) { // Parcours des positions
                // Si l'une des cases recouvertes a une hauteur différente de la hauteur initiale, on renvoie
                // une exception
                if (board->getHeight(*it) != initialHeight)
                    throw PlacementException("Les cases recouvertes ne sont pas de la même hauteur");

                // Si l'une des cases recouvertes a un ID différent de la case initiale, on passe le booléen à true.
                // La contrainte de recouvrement est alors validée.
                if (board->getCell(*it)->getID() != initialID) sameTiletest = true;

                if (board->getCell(*it)->getType() == Type::QUARRY) stoneCount++;
            }

            //  =====/!\ Same tile test un peu bancal et pas très extensible /!\=====
            // Si la contrainte de recouvrement n'est pas validée, on lève une exception
            if (!sameTiletest)
                throw PlacementException("Les cases recouvertes appartiennent toutes à la même tuile");


        } else { // Si l'emplacement de la position initiale est vide
            for (auto it = positions.begin(); it != positions.end(); it++ ) { // Parcours des positions
                if (board->getCell(*it) != nullptr) // Si l'un des emplacements n'est pas vide, le placement est
                    // invalide
                    throw PlacementException("Les cases recouvertes ne sont pas de la même hauteur");
            }
        }

        if (!adjacentIgnore) {
            bool adjacentTest = false;
            for (auto it = positions.begin(); it != positions.end(); it++ ) { // Parcours des positions
                for (auto it_pos = it->begin(); it_pos != it->end(); it_pos++) {
                    // Parcours des voisins de chaque position
                    if (board->getCell(*it_pos) != nullptr) // Si l'une des positions a un emplacement voisin non-vide
                        // le placement est correct
                        adjacentTest = true;
                }
            }
            if (!adjacentTest)
                throw PlacementException("La tuile n'est pas adjacente au reste du plateau");
        }



        unsigned int height = board->getHeight(positions[0])+1; // Hauteur à appliquer

        int i = 0;
        for (auto it = t->begin(); it != t->end(); it++) {
            board->setCell(positions[i],height,*it); // Placement des cases dans le plateau
            i++;
        }

        return stoneCount;
    }

    ostream& operator<<(ostream& f, const BoardManager& c) {
        f << *(c.board);
        return f;
    }


}