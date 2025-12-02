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

    //method called by Game
    //canPlace no longer exists
    //exception
    void Player::playTurn(const Tile& tile) {
        int x = 0;
        int y = 0;
        int r = 0;
        Position pos;
        Rotation rotation;
        cout << "Choose a position (x,y) on your board where you want to put the tile : ";
        cout << "x ? : ";
        cin >> x;
        cout << "y ? : ";
        cin >> y;
        cout << "Choose the rotation of the tile (1 to 5), r : ";
        cin >> r;
        pos = Position(x,y);
        addStones(board.place(&tile,pos,rotation));
        cout << board << endl;
    }
}