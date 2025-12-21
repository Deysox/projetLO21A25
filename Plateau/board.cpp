#include "board.h"

using std::to_string;

namespace Barnabe {

    // ===== maps utilisées pour le chargement/enregistrement de la sauvegarde =====
    map<string, Color> Board::stringToColor = {{"Blue",Color::BLUE},{"Red",Color::RED},{"Green",Color::GREEN},{"Yellow",Color::YELLOW},{"Grey",Color::GREY},{"Purple",Color::PURPLE}};
    map<string, Type> Board::stringToType = {{"District", Type::DISTRICT},{"Place", Type::PLACE},{"Quarry", Type::QUARRY}};
    map<Color, string> Board::colorToString = {
        {Color::BLUE, "Blue"},
        {Color::RED, "Red"},
        {Color::GREEN, "Green"},
        {Color::YELLOW, "Yellow"},
        {Color::GREY, "Grey"},
        {Color::PURPLE, "Purple"}
    };
    map<Type, string> Board::typeToString = {
        {Type::DISTRICT, "District"},
        {Type::PLACE, "Place"},
        {Type::QUARRY, "Quarry"}
    };


    Board::Board() : corner_br(0,0), corner_tl(0,0) {};
    Board::~Board() = default;
    /*Board::Board(const Board& b) {
        cells = b.cells;
        corner_tl = b.corner_tl;
        corner_br = b.corner_br;
    }*/

    Board::Board(const Board& b) {
        corner_tl = b.corner_tl;
        corner_br = b.corner_br;
        for (const auto& [pos, data] : b.cells) {
            Cell* new_cell = new Cell(*data.first);
            cells[pos] = {new_cell, data.second};
        }
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
            jcell["couleur"] = colorToString[data.first->getColor()];
            jcell["type"] = typeToString[data.first->getType()];
            jcell["cell_id"] = data.first->getID();
            jcell["hauteur"] = data.second;
            j_cells.push_back(jcell);
        }

        j_board["cells"] = j_cells;
        return j_board;
    }

    Board Board::fromJsonBoard(const json& j) {
        Board board;
        board.corner_tl = Position(j["corner_tl"]["x"], j["corner_tl"]["y"]);
        board.corner_br = Position(j["corner_br"]["x"], j["corner_br"]["y"]);
        for (const auto& jcell : j["cells"]) {
            int x = jcell["x"];
            int y = jcell["y"];
            unsigned int hauteur = jcell["hauteur"];
            int id = jcell["cell_id"];
            Color color = stringToColor[jcell["couleur"]];
            Type type = stringToType[jcell["type"]];
            const Cell* cell_ptr = new Cell(id, color, type);
            board.setCell(Position(x, y), hauteur, cell_ptr);
        }
        return board;
    }

    Board &Board::operator=(const Board &b ) {
        if (&b != this) {
            cells = b.cells;
            corner_tl = b.corner_tl;
            corner_br = b.corner_br;
        }
        return *this;
    }

    const Cell* Board::getCell(const Position& pos) const {
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

    unsigned int Board::getHeight(const Position& pos) const {
        auto search = cells.find(pos);
        if (search != cells.end()) {
            return search->second.second;
        }
        return 0;

    }

    unsigned int Board::getHeight(int x, int y) const {
        return getHeight(Position(x,y));
    }

    void Board::setCell(const Position& pos, unsigned int h, const Cell* c) {
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

        const Position ctl = b.getCorners().first;
        const Position cbr = b.getCorners().second;

        const int xindex_end = cbr.x()+1; // Le passage sur les colonnes se fait de la première à la dernière de gauche à droite
        const int yindex_end = cbr.y()-1; // Le passage sur les lignes se fait de haut en bas, avec une itération de plus que
        // le nombre de lignes indiqué par les coordonnées. Les lignes d'affichage console sont à cheval sur plusieurs
        // lignes du plateau hexagonal.

        output += "    ";
        for (int xindex = ctl.x()-1; xindex <= xindex_end; xindex++) {
            output += lenStringInt(xindex);
        }
        f << output << "\n";

        // A chaque itération, deux lignes de sortie console sont produites.
        for (int yindex = ctl.y()+1; yindex >= yindex_end; yindex--) {
            string line1; // Partie haute de la ligne
            string line2; // Partie basse de la ligne

            line2 += lenStringInt(yindex);
            line1 += "    ";

            for (int xindex = ctl.x()-1; xindex <= xindex_end; xindex++) {
                if (xindex%2 == 0) { // Si le x est pair, les parties haute et basse correspondent à la même cellule
                    const Cell* cellToPlace = b.getCell(xindex,yindex);
                    const unsigned int heightToPlace = b.getHeight(xindex,yindex);
                    line1 += (cellToPlace ? cellToPlace->displayTop(heightToPlace) : "    "); // Ajout de la partie
                    // haute de la cellule, si présente
                    line2 += (cellToPlace ? cellToPlace->displayBottom() : "    "); // Ajout de la partie basse de la
                    // cellule, si présente
                } else {

                    const Cell* cellToPlace = b.getCell(xindex,yindex+1);
                    line1 += (cellToPlace ? cellToPlace->displayBottom() : "    ");

                    cellToPlace = b.getCell(xindex,yindex);
                    const unsigned int heightToPlace = b.getHeight(xindex,yindex);

                    line2 += (cellToPlace ? cellToPlace->displayTop(heightToPlace) : "    ");
                }
            }
            f << line1 << "\n" << line2 << "\n";
        }
        return f;
    }

    string lenStringInt(int x) {
        string output = to_string(x);

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