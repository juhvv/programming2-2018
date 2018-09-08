#include "player.hh"
#include <iostream>

Player::Player(std::string name):
    name_(name), points_(0)    {

}

std::string Player::get_name() const {
    return name_;
}

int Player::get_points() const {
    return points_;
}

bool Player::has_won() const {
    if ( points_ == 50 ) {
        return 1;

    } else {
        return 0;
    }
}

void Player::add_points(int pts) {
    points_ += pts;
    if ( points_ > 50 ) {
        std::cout << name_ << " gets penalty points!" << std::endl;
        points_ = 25;
    }
}
