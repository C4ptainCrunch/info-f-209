#include "Ball.h"

Ball::Ball(): speed_(0) {
    position_.y = 0;
    position_.y = 0;
}

Ball::Ball(int speed): speed_(speed) {
    position_.x = 0;
    position_.y = 0;
}

Ball::Ball(int speed, Position position): speed_(speed), position_(position) {}

Ball::~Ball() {}

void Ball::setPosition(int x, int y) {
    position_.x = x;
    position_.y = y;
}

Position Ball::getPosition() {
    return position_;
}

void Ball::setPosition(Position position) {
    position_ = position;
}

int Ball::getSpeed() const {
    return speed_;
}
