#include "player.h"

namespace Barnabe {
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

    ostream& operator<<(ostream& f, const Barnabe::Player& p) {
        f << "name : " << p.getName() << "\n" << "stones : " << p.getStones() << "\n" << "board : " << p.getBoard() << endl;
        return f;
    }

    void Player::playTurn(const Tile& tile) {
        bool placed = false;
        while (!placed) {
            int x = 0, y = 0, r = 0;
            cout << "Choose a position (x,y) on your board where you want to put the tile :\n";
            cout << "x ? : "; cin >> x;
            cout << "y ? : "; cin >> y;
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