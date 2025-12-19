#include "player.h"

namespace Eloise {
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

    const Barnabe::BoardManager& Player::getBoard() const {
        return board;
    }

    ostream& operator<<(ostream& f, const Player& p) {
        f << "\n-- Player " << p.getName()  << " --\nStones : " << p.getStones() <<  "\nBoard :\n" <<  p.getBoard();
        return f;
    }

}