#include "Player.h"

const string& Player::GetName() const {
    return mName;
}

int Player::GetHighestLevel() const {
    return mHighestLevel;
}

void Player::SetHighestLevel(int highestLevel) {
    this->mHighestLevel = highestLevel;
}

void Player::SetName(const string& name) {
    this->mName = name;
}

Player::Player() {
    mName = "";
    mHighestLevel = 0;

}
