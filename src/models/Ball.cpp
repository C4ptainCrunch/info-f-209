#include "Ball.h"

Ball::Ball(int speed):speed_(speed){ }

Ball::~Ball(){

}

Position Ball::getPosition(){
	return position_;
}

Ball::setPosition(Position position){
	position_ = position;
}