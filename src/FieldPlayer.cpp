#include "FieldPlayer.h"

FieldPlayer::FieldPlayer(){}

FieldPlayer::~FieldPlayer(){}

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
