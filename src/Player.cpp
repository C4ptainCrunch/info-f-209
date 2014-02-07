#include "Player.h"

Player::Player(int speed, int force, int agility, int reflexes, int passPrecision, bool wounded, vector<Item> inventory) : speed_(speed), force_(force), agility_(agility), reflexes_(reflexes), passPrecision_(passPrecision), wounded_(wounded), inventory_(inventory){}

Player::Player(): speed_(1), force_(1), agility_(1), reflexes_(1), passPrecision_(1), wounded_(false){
	inventory_ = std::vector<Item>;
}

