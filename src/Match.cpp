#include "Match.h"

Match::Match(Club& host, Club& guest){
	clubs_[0] = &host;
	clubs_[1] = &guest;

    goldenSnitch_ = GoldenSnitch();
    quaffle_ = Quaffle();
    budgers_[0] = Budger();
    budgers_[1] = Budger();

    for (int i = 0; i< WIDTH; ++i){
    	for (int j = 0; j < LENGHT; ++j){
    		struct Case caseUnit;
    		caseUnit.type = 1;
    		caseUnit.player = NULL;
    		caseUnit.ball = NULL;
    		grid_[i][j] = caseUnit;
    	}
    }
}

Match::~Match(){}

int* Match::getScore(){
	return score_;
}

int Match::addPoint(bool guestTeam ,int delta){
	score_[guestTeam] += delta;
	return score_[guestTeam];
}
