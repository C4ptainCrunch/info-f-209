#include "Match.h"

Match::Match(Club& host, Club& guest){
	clubs_[0] = &host;
	clubs_[1] = &guest;

    goldenSnitch_ = GoldenSnitch();
    quaffle_ = Quaffle();
    budgers_[2] = {Budger(),Budger()} ;
}

Match::~Match(){}

int* Match::getScore(){
	return score_;
}

int Match::addPoint(bool guestTeam ,int delta){
	score_[guestTeam] += delta;
	return score_[guestTeam];
}