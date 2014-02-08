#include "Player.h"

using namespace std;

Player::Player(int speed, int force, int agility, int reflexes, int passPrecision, bool wounded, vector<Item> inventory) : speed_(speed), force_(force), agility_(agility), reflexes_(reflexes), passPrecision_(passPrecision), wounded_(wounded), inventory_(inventory){}

Player::Player(): speed_(1), force_(1), agility_(1), reflexes_(1), passPrecision_(1), wounded_(false){
	inventory_ = std::vector<Item>();
}

Player::~Player(){ }

int Player::getSpeed(){
	return speed_;
}

int Player::getForce(){
	return force_;
}

int Player::getAgility(){
	return agility_;
}

int Player::getReflexes(){
	return reflexes_;
}

int Player::getPassPrecision(){
	return speed_;
}

bool Player::isWounded(){
	return wounded_;
}

void Player::setWoundedState(bool wound){
	wounded_ = wound;
}

vector<Item> Player::getInventory(){
	return inventory_;
}

void Player::setSpeed(int speed){
	speed_ = speed;
}

void Player::setForce(int force){
	force_ = force;
}

void Player::setAgility(int agility){
	agility_ = agility;
}

void Player::setReflexes(int reflexes){
	reflexes_ = reflexes;
}

void Player::setPassPrecision(int passPrecision){
	passPrecision_ = passPrecision;
}

void Player::setWoundState(bool woundState){
	wounded_ = woundState;
}

Item removeItem(string itemType){
	//TODO convert string to position
	return Item();
}

Item Player::removeItem(unsigned int position){
	Item* tempItem = &(inventory_[position]);
	inventory_.at(position) = Item();
	return *tempItem;
}

void addToInventory(Item newItem){
	//TODO
}
