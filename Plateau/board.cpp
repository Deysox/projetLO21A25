#include "board.h"

namespace Barnabe {
    using namespace Marilou;

    Board::Board() : corner_br(0,0), corner_tl(0,0) {};
    Board::~Board() = default;
    Board::Board(const Board& b) {
        cells = b.cells;
        corner_tl = b.corner_tl;
        corner_br = b.corner_br;
    }

    json Board::toJsonBoard() const {
        json j_board;

        j_board["corner_tl"] = { {"x", corner_tl.x()}, {"y", corner_tl.y()} };
        j_board["corner_br"] = { {"x", corner_br.x()}, {"y", corner_br.y()} };

        json j_cells = json::array();
        for (const auto& [pos, data] : cells) {
            json jcell;
            jcell["x"] = pos.x();
            jcell["y"] = pos.y();
            jcell["cell_id"] = data.first->getID();
            jcell["hauteur"] = data.second;
            j_cells.push_back(jcell);
        }

        j_board["cells"] = j_cells;
        return j_board;
    }

    Board &Board::operator=(const Board &b ) {
        if (&b != this) {
            cells = b.cells;
            corner_tl = b.corner_tl;
            corner_br = b.corner_br;
        }
        return *this;
    }

    const Cell* Board::getCell(Position pos) const {
        auto search = cells.find(pos); // Recherche de l'emplacement pos dans la map
        if (search != cells.end()) {
            return search->second.first; // Si l'emplacement est occupé, on renvoie la case
        } else {
            return nullptr; // Sinon, on renvoie nullptr
        }
    }

    const Cell *Board::getCell(int x, int y) const {
        return getCell(Position(x,y));  // Voir getCell(Position pos)
    }

    unsigned int Board::getHeight(Position pos) const {
        auto search = cells.find(pos);
        if (search != cells.end()) {
            return search->second.second;
        }
        return 0;

    }

    unsigned int Board::getHeight(int x, int y) const {
        return getHeight(Position(x,y));
    }

    void Board::setCell(Position pos, unsigned int h, const Cell* c) {
        cells[pos] = pair<const Cell*, unsigned int>(c,h); // Actualisation de la map

        // Actualisation des coins
        if (pos.x() < corner_tl.x()) corner_tl = Position(pos.x(),corner_tl.y());
        else if (pos.x() > corner_br.x()) corner_br = Position(pos.x(),corner_br.y());

        if (pos.y() > corner_tl.y()) corner_tl = Position(corner_tl.x(),pos.y());
        else if (pos.y() < corner_br.y()) corner_br = Position(corner_br.x(),pos.y());
    }

    void Board::setCell(int x, int y, unsigned int h, const Cell *c) {
        setCell(Position(x,y),h,c);
    }


    std::pair<Position, Position> Board::getCorners() const {
        return {corner_tl,corner_br};
    }

    ostream& operator<<(ostream& f, const Barnabe::Board& b) {
        string output;

        Position ctl = b.getCorners().first;
        Position cbr = b.getCorners().second;

        int xindex_end = cbr.x(); // Le passage sur les colonnes se fait de la première à la dernière de gauche à droite
        int yindex_end = cbr.y()-1; // Le passage sur les lignes se fait de haut en bas, avec une itération de plus que
        // le nombre de lignes indiqué par les coordonnées. Les lignes d'affichage console sont à cheval sur plusieurs
        // lignes du plateau hexagonal.

        output += "    ";
        for (int xindex = ctl.x(); xindex <= xindex_end; xindex++) {
            output += lenStringInt(xindex);
        }
        f << output << endl;

        // A chaque itération, deux lignes de sortie console sont produites.
        for (int yindex = ctl.y(); yindex >= yindex_end; yindex--) {
            string line1; // Partie haute de la ligne
            string line2; // Partie basse de la ligne

            line2 += lenStringInt(yindex);
            line1 += "    ";

            for (int xindex = ctl.x(); xindex <= xindex_end; xindex++) {
                if (xindex%2 == 0) { // Si le x est pair, les parties haute et basse correspondent à la même cellule
                    const Cell* cellToPlace = b.getCell(xindex,yindex);
                    unsigned int heightToPlace = b.getHeight(xindex,yindex);
                    line1 += (cellToPlace ? cellToPlace->displayTop(heightToPlace) : "    "); // Ajout de la partie
                    // haute de la cellule, si présente
                    line2 += (cellToPlace ? cellToPlace->displayBottom() : "    "); // Ajout de la partie basse de la
                    // cellule, si présente
                } else {

                    const Cell* cellToPlace = b.getCell(xindex,yindex+1);
                    line1 += (cellToPlace ? cellToPlace->displayBottom() : "    ");

                    cellToPlace = b.getCell(xindex,yindex);
                    unsigned int heightToPlace = b.getHeight(xindex,yindex);

                    line2 += (cellToPlace ? cellToPlace->displayTop(heightToPlace) : "    ");
                }
            }
            f << line1 << endl << line2 << endl;
        }
        return f;
    }

    string lenStringInt(int x) {
        string output = to_string(x);

        //cout << output.length() << endl;
        switch (output.length()) {
            case 4:
                break;
            case 3:
                output = " "+output;
                break;
            case 2:
                output = " "+output+" ";
                break;
            case 1:
                output = "  "+output+" ";
                break;
            default:
                throw;
        }
        return output;

    }


}