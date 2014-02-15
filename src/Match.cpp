#include <iostream>

#include "Match.h"

using namespace std;



Match::Match(Club& host, Club& guest){
    clubs_[0] = &host;
    clubs_[1] = &guest;

    for (int i = 0; i< 2 ;++i){
        cout<<"i : "<<i<<endl;
        for (int j = 0; j < 7; ++j){
            cout<<"j : "<<j;
            //teams_[i][j] = FieldPlayer(clubs_[i]->getTeam()->getPlayers()[j],0); TO IMPROVE
        }
    }

    goldenSnitch_ = GoldenSnitch();
    quaffle_ = Quaffle();
    budgers_[0] = Budger();
    budgers_[1] = Budger();
    generateFieldPlayers(); 
    generateGrid();

}


Match::~Match(){}

void Match::generateFieldPlayers(){
    for (int i = 0; i< 2 ;++i){
        for (int j = 0; j < 7; ++j){
            if (j ==0){
                teams_[i][j].setRole(KEEPER);
            }
            else if (j>0 and j<=3){
                teams_[i][j].setRole(CHASER);
            }
            else if (j>3 and j<=5){
                teams_[i][j].setRole(BEATER);
            }
            else{
                teams_[i][j].setRole(SEEKER);
            }
        }

    }
}

void Match::generateGrid(){
    double diameterFactor = 46.0/100.0;// Normalement c'est la moitié de la longueur/largeur 
    int delta = 1/2; //Delta qui permet d'éviter les bugs lors de l'affichage de la matrice

    for (int i = 0; i<WIDTH;++i){
        for (int j=0; j<LENGHT;++j){
            grid_[i][j].type = USABLE;
            // equation d'une ellipse non centrée : (x-h)²/a² + (x-k)²/b²
            //avec x = i, h et k sont les coord du centre, a et b les demi longueurs de l'ellipse
            double result = pow(i-WIDTH/2.0, 2)/pow(diameterFactor*WIDTH, 2);
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
                else if(j == 2*LENGHT/15 or j == 13 * LENGHT/15){
                    FieldPlayer *tempPlayer = new FieldPlayer(KEEPER);
                    grid_[i][j].player = tempPlayer;
                    //cout<<endl<<"Le role des batteurs est : "<<grid_[i][j].player->getRole()<<endl;
                }
                else if(j == 7*LENGHT/30 or j == 23*LENGHT/30){
                    FieldPlayer *tempPlayer = new FieldPlayer(SEEKER);
                    grid_[i][j].player = tempPlayer;
                    //cout<<endl<<"Le role des attrapeurs est : "<<grid_[i][j].player->getRole()<<endl;
                }
                else if(j == 5*LENGHT/30 or j == 25*LENGHT/30){
                    FieldPlayer *tempPlayer = new FieldPlayer(CHASER);
                    grid_[i][j].player = tempPlayer;
                    //cout<<endl<<"Le role des poursuiveurs est : "<<grid_[i][j].player->getRole()<<endl;
                }
            }
            else if (i == WIDTH/2 - WIDTH/15 or i== WIDTH/2 + WIDTH/15){
                if(j == 2 * LENGHT/15 or j == 13 * LENGHT/15){
                    grid_[i][j].type = GOAL;//goals latéraux
                }
                else if (j == 5*LENGHT/30 or j == 25*LENGHT/30){
                    FieldPlayer *tempPlayer = new FieldPlayer(CHASER);
                    grid_[i][j].player = tempPlayer;
                    //cout<<endl<<"Le role des poursuiveurs est : "<<grid_[i][j].player->getRole()<<endl;
                }
            }
            else if (i == WIDTH/2 - WIDTH/30 or i == WIDTH/2 + WIDTH/30){
                if(j == 6*LENGHT/30 or j == 24*LENGHT/30){
                    FieldPlayer *tempPlayer = new FieldPlayer(BEATER);
                    grid_[i][j].player = tempPlayer;
                }
            }
    //--------------------------BALLS----------------------------------
            


        }
    }
}

void Match::movePlayer(int fromX, int fromY,int toX, int toY){

}

int* Match::isInTheWay(int fromX,int fromY,int toX, int toY){
    int blockingPosition[2];
    return blockingPosition;
}

bool Match::isPlayerInGuestTeam(FieldPlayer& fieldPlayer){
    bool playerInGuestTeam = false;
    for (int i = 0; i<7; ++i){
        if (teams_[1][i] == fieldPlayer){
            playerInGuestTeam = false;
        }
    }
    return playerInGuestTeam;
}

string Match::print(){ //FOR TEST PURPOSES
    string c;
    for (int i = 0; i<WIDTH;++i){
        if (i%2 != 0){ 
            c+=" ";
        }
        for (int j=0; j<LENGHT;++j){
            if (grid_[i][j].type == USABLE){
                
                if (grid_[i][j].player != 0){
                
                    if (grid_[i][j].player->getRole() == KEEPER){
                        c+= "K ";
                    }
                    else if(grid_[i][j].player->getRole() == CHASER){
                        c+= "C ";
                    }
                    else if(grid_[i][j].player->getRole() == SEEKER){
                        c+= "S ";
                    }
                    else if(grid_[i][j].player->getRole() == BEATER){
                        if (isPlayerInGuestTeam(*grid_[i][j].player)){
                            c+= "\e[0;34m B \e[0m";
                        }
                        else{
                            c+= "\e[0;31m B \e[0m";

                        }
                    }
                    delete grid_[i][j].player;
                }
                else{
                    c += "\u2B21 ";
                }
                
            }
            else if (grid_[i][j].type == GOAL){
                c += "오";
            }
            else{
                c += "\u2B22 ";
            }
            
            //cout<< matrix[i][j]<<" ";
        }
        c+="\n";
    }
    return c;
}

int* Match::getScore(){
    return score_;
}

int Match::addPoint(bool guestTeam ,int delta){
    score_[guestTeam] += delta;
    return score_[guestTeam];
}

void Match::moveBalls(){
    Position pos;
    pos.x = 0;
    pos.y = 0;
    goldenSnitch_.autoMove(pos);
    for (int i = 0; i<2;++i){
        budgers_[i].autoMove(pos);
    }

}

bool Match::checkEndOfMatch(){
    bool goldenSnitchCaught = false;
    for (int i = 0; i< WIDTH; ++i){
        for (int j = 0; j < LENGHT; ++j){
            if (grid_[i][j].ball == &goldenSnitch_){
                //IF player = Attrapeur;
                goldenSnitchCaught = true;
            }
        }
    }
    return goldenSnitchCaught;

}
