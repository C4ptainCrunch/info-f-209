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

void Match::moveBalls(){
    goldenSnitch_.automove();
    for (int i = 0; i<2;++i){
        budgers_[i].automove();
    }

}

bool Match::checkEndOfMatch(){
    bool goldenSnitchCaught = false;
    for (int i = 0; i< WIDTH; ++i){
        for (int j = 0; j < LENGHT; ++j){
            if (grid_[i][j].ball == goldenSnitch_){
                //IF player = Attrapeur;
                goldenSnitchCaught = true;
            }
        }
    }
    return goldenSnitchCaught;

}
