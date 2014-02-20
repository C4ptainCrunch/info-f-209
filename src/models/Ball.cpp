#include "Ball.h"

Ball::Ball(int speed):speed_(speed){
	position_.x = 0;
	position_.y = 0;
}

Ball::~Ball(){

}

void Ball::setPosition(int x, int y){
	position_.x = x;
	position_.y = y;
}

Position Ball::getPosition(){
	return position_;
}

Ball::setPosition(Position position){
	position_ = position;
}