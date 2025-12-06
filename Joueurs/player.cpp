#include "player.h"
#include <QInputDialog>
#include <QMessageBox>

namespace Eloise {
    using namespace Barnabe;

    size_t Player::stones_distribution = 1;

    Player::Player(const string& s) : name(s), stones(stones_distribution) {
        stones_distribution++;
    }

    Player::~Player(){}

    const string& Player::getName() const {
        return name;
    }

    int Player::getStones() const {
        return stones;
    }

    void Player::setStones(int n) {
        stones = n;
    }

    void Player::addStones(int n) {
        stones += n;
    }

    const BoardManager& Player::getBoard() const {
        return board;
    }

    ostream& operator<<(ostream& f, const Player& p) {
        f << "Player " << p.getName() << endl << "Stones : " << p.getStones() << endl << "board : " << endl << p.getBoard() << endl;
        return f;
    }

    void Player::playTurn(const Tile& tile) {
        cout << "\n" << board << endl;
        bool placed = false;
        while (!placed) {
            int x = 0, y = 0, r = 0;
            cout << "Choose a position (x,y) on your board where you want to put the tile." << endl;
            cout << "x : "; cin >> x;
            cout << "y : "; cin >> y;
            cout << "Choose the rotation of the tile (0 to 5), r : "; cin >> r;
            Position pos(x,y);
            Rotation rotation(r);
            try {
                addStones(board.place(&tile, pos, rotation));
                placed = true;
            }
            catch(const PlacementException& pe) {
                cout << "Error : " << pe.what() << "\n";
            }
            catch(const TileException& te) {
                cout << "Error : " << te.what() << "\n";
            }
        }
        cout << board << endl;
    }

    void Player::playTurnQt(const Tile& tile, QWidget* parent) {
        bool placed = false;
        while (!placed) {
            int x = QInputDialog::getInt(parent, "Place a tile", "x :");
            int y = QInputDialog::getInt(parent, "Place a tile", "y :");
            int r = QInputDialog::getInt(parent, "Rotation", "Rotation (0 à 5) :", 0, 0, 5);
            Position pos(x, y);
            Rotation rotation(r);
            try {
                addStones(board.place(&tile, pos, rotation));
                placed = true;
            }
            catch (const std::exception& e) {
                QMessageBox::warning(parent, "Error", e.what());
            }
        }
        //to be coded : something to show board if changed
        //emit boardChanged();
    }

    void Architect::playTurn(const Tile& t) {
        architect_tiles.push_back(const_cast<Tile*>(&t));
        //score based on the difficulty level
        /*switch (difficulty) {
            case 1:
                break;
            case 2:1
                break;
            case 3:
                break;
        }*/
    }
}