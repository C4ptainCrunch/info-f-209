#include "Match.h"


Match::Match(Club& host, Club& guest){
    clubs_[0] = &host;
    clubs_[1] = &guest;

    goldenSnitch_ = GoldenSnitch();
    quaffle_ = Quaffle();
    budgers_[0] = Budger();
    budgers_[1] = Budger();
    generateGrid();

}


Match::~Match(){}

void Match::generateGrid(){
    float diameterFactor = 46.0/100.0;// Normalement c'est la moitié de la longueur/largeur 
    int delta = 1/2; //Delta qui permet d'éviter les bugs lors de l'affichage de la matrice

    for (int i = 0; i<WIDTH;++i){
        for (int j=0; j<LENGHT;++j){
            grid_[i][j].type = USABLE;
            // equation d'une ellipse non centrée : (x-h)²/a² + (x-k)²/b²
            //avec x = i, h et k sont les coord du centre, a et b les demi longueurs de l'ellipse
            float result = pow(i-WIDTH/2.0, 2)/pow(diameterFactor*WIDTH, 2);
            result+= pow(j-LENGHT/2.0, 2)/pow(diameterFactor*LENGHT, 2);
            if (i%2 !=0){
                result -= delta;
            }
            if (result>1){//Si on est à l'extérieur de l'ellipse
                grid_[i][j].type = VOID;
            }
    //----------------------------GOALS---------------------------------
            if( i == WIDTH/2){
                if (j == LENGHT/15 + LENGHT/20 or j == LENGHT*14/15 - LENGHT/20){
                    grid_[i][j].type = GOAL;//goal central
                }
            }
            if (i == WIDTH/2 - WIDTH/15 or i== WIDTH/2 + WIDTH/15){
                if(j == 2 * LENGHT/15 or j == 13 * LENGHT/15){
                    grid_[i][j].type = GOAL;//goals latéraux
                }
            }
        }
    }
}

int* Match::getScore(){
    return score_;
}

int Match::addPoint(bool guestTeam ,int delta){
    score_[guestTeam] += delta;
    return score_[guestTeam];
}

void Match::moveBalls(){
    goldenSnitch_.autoMove();
    for (int i = 0; i<2;++i){
        budgers_[i].autoMove();
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
