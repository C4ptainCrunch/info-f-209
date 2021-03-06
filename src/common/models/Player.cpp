#include "Player.h"

using namespace std;

Player::Player(int speed, int force, int agility, int reflexes, int passPrecision, bool wounded, vector<Item> inventory): speed_(speed), force_(force), agility_(agility), reflexes_(reflexes), passPrecision_(passPrecision), wounded_(wounded), inventory_(inventory) {}

Player::Player(): speed_(10), force_(10), agility_(10), reflexes_(10), passPrecision_(10), wounded_(false), inventory_() {}

Player::~Player() {}

int Player::getSpeed() const {
    return speed_;
}

int Player::getForce() const {
    return force_;
}

int Player::getAgility() const {
    return agility_;
}

int Player::getReflexes() const {
    return reflexes_;
}

int Player::getPassPrecision() const {
    return speed_;
}

bool Player::isWounded() const {
    return wounded_;
}

void Player::setWoundedState(bool wound) {
    wounded_ = wound;
}

vector<Item> Player::getInventory() const {
    return inventory_;
}

void Player::setSpeed(int speed) {
    speed_ = speed;
}

void Player::setForce(int force) {
    force_ = force;
}

void Player::setAgility(int agility) {
    agility_ = agility;
}

void Player::setReflexes(int reflexes) {
    reflexes_ = reflexes;
}

void Player::setPassPrecision(int passPrecision) {
    passPrecision_ = passPrecision;
}

void Player::setWoundState(bool woundState) {
    wounded_ = woundState;
}
