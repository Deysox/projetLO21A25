//
// Created by barnab on 17/11/2025.
//
#include "boardmanager.h"
#include "../Utilitaires/exceptions.h"

namespace Barnabe {
    BoardManager::BoardManager() : board(new Board()) {
        startingTile = new StartingTile(); // Initialisation du plateau en y ajoutant une tuile de départ
        place(startingTile,Position(0,0),0, true);
    }

    BoardManager::BoardManager(const BoardManager &e) : startingTile(new StartingTile) {
        board = new Board();
        *board = *(e.board);

    }

    BoardManager& BoardManager::operator=(const BoardManager& e) {
        if (&e != this) {
            delete board;
            board = new Board(*e.board);
        }
        return *this;
    }

    BoardManager::~BoardManager() {
        delete board; // Désallocation du Board
        delete startingTile; // Désallocation de la tuile de départ
    }


    int BoardManager::place(const Tile *t, const Position& p, const Rotation& r, bool adjacentIgnore) {
        vector<Position> positions = t->calculatePositions(p,r); // Calcul des positions à vérifier

        int stoneCount = 0;

        Position initialPos = positions[0]; // Position initiale utilisée comme base de comparaison
        const Cell* initialCell = board->getCell(initialPos); // Cellule initiale
        unsigned int initialHeight = board->getHeight(initialPos); // Hauteur initiale


        if (initialCell) { // S'il y a déjà une cellule dans la position intiale
            int initialID = initialCell->getID();
            bool sameTiletest = false;
            for (const Position& pos : positions) { // Parcours des positions
                // Si l'une des cases recouvertes a une hauteur différente de la hauteur initiale, on renvoie
                // une exception
                if (board->getHeight(pos) != initialHeight)
                    throw PlacementException("Recovered cells have different heights");

                // Si l'une des cases recouvertes a un ID différent de la case initiale, on passe le booléen à true.
                // La contrainte de recouvrement est alors validée.
                if (board->getCell(pos)->getID() != initialID) sameTiletest = true;

                if (board->getCell(pos)->getType() == Type::QUARRY) stoneCount++;
            }

            //  =====/!\ Same tile test un peu bancal et pas très extensible /!\=====
            // Si la contrainte de recouvrement n'est pas validée, on lève une exception
            if (!sameTiletest)
                throw PlacementException("All recovered cells belong to the same tile");


        } else { // Si l'emplacement de la position initiale est vide
            for (const Position& pos : positions) { // Parcours des positions
                if (board->getCell(pos) != nullptr) // Si l'un des emplacements n'est pas vide, le placement est
                    // invalide
                    throw PlacementException("Recovered cells have different heights");
            }
        }

        if (!adjacentIgnore) {
            bool adjacentTest = false;
            for (const Position& pos : positions) { // Parcours des positions
                for (const Position& posvoisins : pos) {
                    // Parcours des voisins de chaque position
                    if (board->getCell(posvoisins) != nullptr) // Si l'une des positions a un emplacement voisin non-vide
                        // le placement est correct
                        adjacentTest = true;
                }
            }
            if (!adjacentTest)
                throw PlacementException("Tile is not adjacent to the board");
        }



        unsigned int height = board->getHeight(positions[0])+1; // Hauteur à appliquer

        int i = 0;
        for (const Cell* cell : *t) { // Parcours de la tuile
            board->setCell(positions[i],height,cell); // Placement des cases dans le plateau
            i++;
        }

        return stoneCount;
    }

    ostream& operator<<(ostream& f, const BoardManager& c) {
        f << *(c.board);
        return f;
    }


}