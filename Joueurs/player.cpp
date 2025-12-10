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
        f << "Player " << p.getName() << endl << "Stones : " << p.getStones() << endl << "board : " << endl << p.getBoard() << endl;
        return f;
    }

}