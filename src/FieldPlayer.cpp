#include "FieldPlayer.h"


FieldPlayer::FieldPlayer(int role): role_(role){}

FieldPlayer::FieldPlayer(): role_(0){}

FieldPlayer::~FieldPlayer(){}

FieldPlayer::FieldPlayer(NonFieldPlayer& nonFieldPlayer, int role){
        speed_ = nonFieldPlayer.getSpeed();
        force_ = nonFieldPlayer.getForce();
        agility_ = nonFieldPlayer.getAgility();
        reflexes_ = nonFieldPlayer.getReflexes();
        passPrecision_ = nonFieldPlayer.getPassPrecision();
        wounded_ = nonFieldPlayer.isWounded();
        inventory_ = nonFieldPlayer.getInventory();
        role_ = role;

}

FieldPlayer& FieldPlayer::operator=(Player& player)
{
    if (this != &player){
        speed_ = player.getSpeed();
        force_ = player.getForce();
        agility_ = player.getAgility();
        reflexes_ = player.getReflexes();
        passPrecision_ = player.getPassPrecision();
        wounded_ = player.isWounded();
        inventory_ = player.getInventory();
    }
    return *this;
}
void FieldPlayer::move(){}

void FieldPlayer::hitBudger(){}

void FieldPlayer::catchGoldenSnitch(){}

void FieldPlayer::throwQuaffle(){}

void FieldPlayer::catchQuaffle(){}

void FieldPlayer::testMove(){}

void FieldPlayer::setRole(int role){
    role_ = role;
}

int FieldPlayer::getRole(){
    return role_;
}