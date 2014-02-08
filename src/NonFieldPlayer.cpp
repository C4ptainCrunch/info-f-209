#include "NonFieldPlayer.h"

NonFieldPlayer::NonFieldPlayer(int vocation, int speed, int force, int agility, int reflexes, int passPrecision, bool wounded, std::vector<Item> inventory, int level, int experience) : level_(level), experience_(experience), vocation_(vocation) {
	Player(speed, force, agility, reflexes, passPrecision, wounded, inventory);
}

NonFieldPlayer::~NonFieldPlayer(){}

NonFieldPlayer & NonFieldPlayer::operator=(const Player & player){
	if (this != &player){
        speed_ = player.getSpeed();
        force_ = player.getForce();
        agility_ = player.getAgility();
        reflexes_ = player.getReflexes();
        passPrecision_ = player.getPassPrecision();
        wounded_ = player.isWounded();
        inventory_ = player.getInventory();
	}
}

int NonFieldPlayer::getLevel(){
	return level_;
}

void NonFieldPlayer::changeExperience(int deltaExperience){
	experience_ += deltaExperience;
}

void NonFieldPlayer::levelUp(){
	level_ += 1;
}

int NonFieldPlayer::getVocation(){
	return vocation_;
}

void NonFieldPlayer::setVocation(int vocation){
	vocation_ = vocation;
}
