#include "NonFieldPlayer.h"

NonFieldPlayer::NonFieldPlayer(int vocation, int level, int experience) : level_(level), experience_(experience), vocation_(vocation) {}

NonFieldPlayer::~NonFieldPlayer(){}

NonFieldPlayer & NonFieldPlayer::operator=(const Player & player){
	if (this != &player){

		//TODO
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
