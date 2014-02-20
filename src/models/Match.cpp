#include <iostream>

#include "Match.h"

using namespace std;



Match::Match(Club& hostClub, Club& guestClub){
    clubs_[host] = &hostClub;
    clubs_[guest] = &guestClub;


    goldenSnitch_ = GoldenSnitch();
    quaffle_ = Quaffle();
    budgers_[0] = Budger();
    budgers_[1] = Budger();
    generateGrid(); 

}


Match::~Match(){}

void Match::generateFieldPlayers(){
    for (int i = 0; i< 2 ;++i){
        for (int j = 0; j < 7; ++j){
            NonFieldPlayer player = clubs_[i]->getTeam()->getPlayers()[j];
            teams_[i][j] = FieldPlayer(player ,0, i); 
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

    generateFieldPlayers();

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
                else if(j == 2*LENGHT/15){
                    grid_[i][j].player = &teams_[0][0];
                }
                else if (j == 13 * LENGHT/15){
                    grid_[i][j].player = &teams_[1][0];
                }
                else if(j == 7*LENGHT/30){
                    grid_[i][j].player = &teams_[0][6];
                }
                else if(j == 23*LENGHT/30){
                    grid_[i][j].player = &teams_[1][6];
                }
                else if(j == 5*LENGHT/30){
                    grid_[i][j].player = &teams_[0][1];

                }
                else if(j == 25*LENGHT/30){
                    grid_[i][j].player = &teams_[1][1];
                }
            }
            else if (i == WIDTH/2 - WIDTH/15){
                if(j == 2 * LENGHT/15 or j == 13 * LENGHT/15){
                    grid_[i][j].type = GOAL;//goals latéraux
                }
                else if (j == 5*LENGHT/30){
                    grid_[i][j].player = &teams_[0][2];

                }
                else if(j == 25*LENGHT/30){
                    grid_[i][j].player = &teams_[1][2];
                }
            }
            else if (i== WIDTH/2 + WIDTH/15){
                if(j == 2 * LENGHT/15 or j == 13 * LENGHT/15){
                    grid_[i][j].type = GOAL;//goals latéraux
                }
                else if (j == 5*LENGHT/30){
                    grid_[i][j].player = &teams_[0][3];

                }
                else if(j == 25*LENGHT/30){
                    grid_[i][j].player = &teams_[1][3];
                }
            }
            else if (i == WIDTH/2 - WIDTH/30){
                if(j == 6*LENGHT/30){
                    grid_[i][j].player = &teams_[0][4];

                }
                else if(j == 24*LENGHT/30){
                    grid_[i][j].player = &teams_[1][4];
                }

            }
            else if (i == WIDTH/2 + WIDTH/30){
                if(j == 6*LENGHT/30){
                    grid_[i][j].player = &teams_[0][5];

                }
                else if(j == 24*LENGHT/30){
                    grid_[i][j].player = &teams_[1][5];
                }
            }
    //--------------------------BALLS----------------------------------
            


        }
    }

}

void Match::movePlayer(Position fromPos, Position toPos){
    grid_[toPos.x][toPos.y].player = grid_[fromPos.x][toPos.y].player;
    grid_[fromPos.x][fromPos.y].player = 0;
}

Case* Match::newTurn(Way playerWays[14]){
    bool moved = true;
    int turnNumber = 0;
    while (moved && !endGame_){
        moved = false;
        Position nextPosition[14];
        for (int i = 0; i<14; ++i){
            if (playerWays[i].size() >1){
                if (grid_[playerWays[i][turnNumber + 1].x][playerWays[i][turnNumber + 1].y].player == 0){
                    nextPosition.[i] = playerWays[i][turnNumber + 1];
                    movePlayer(playerWays[i][turnNumber], playerWays[i][turnNumber + 1]);
                }
                else{
                    resolveConflict(nextPosition, playerWays, i, turnNumber);
                }
                moved = true;
            }
        }
        ++turnNumber;
    }
}
void Match::resolveConflict(Position nextPosition[14], Way playerWays[14], int indexOne, int turnNumber){
    FieldPlayer playerOne = grid_[ways[indexOne][turnNumber + 1].x][ways[indexOne][turnNumber + 1].y].player;//joueur sur la case causant la merde
    FieldPlayer playerTwo = grid_[ways[indexOne][turnNumber].x][ways[indexOne][turnNumber].y].player;//joueur qui vient foutre la merde
    if (playerOne.getForce() >= playerTwo.getForce()){
        playerWays[indexOne].insert(turnNumber + 1, ways[indexOne][turnNumber])//le joueur le plus faible perd un déplacement(le dernier)
        nextPosition[turnNumber] = ways[indexOne][turnNumber];
    }
    else  if (playerOne.getForce() < playerTwo.getForce()){
        int indexTwo = findIndex(nextPosition, ways[indexOne][turnNumber + 1]);
        // Faire reculer le joueur qui etait avancé et qui doit retourner à la position précédente
        nextPosition[indexTwo] = ways[indexTwo][turnNumber];
        movePlayer(playerWays[indexTwo][turnNumber + 1], playerWays[indexTwo][turnNumber]);
        playerWays[indexTwo].insert(turnNumber + 1, ways[indexTwo][turnNumber])//le joueur le plus faible perd un déplacement(le dernier)

        // Faire avancer le joueur qui a gagné
        nextPosition[indexOne] = ways[indexOne][turnNumber + 1];
        movePlayer(playerWays[indexOne][turnNumber], playerWays[indexOne][turnNumber + 1]);
    }
}

int Match::findIndex(Position nextPosition[14], Position position){
    for (int i = 0; i<14; ++i){
        if (nextPosition[i] = position){
            return i;
        }
    }
    return -1;
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
                    if (! grid_[i][j].player->isInGuestTeam()){
                        c+="\033[1;94m";
                    }
                    else{
                        c+="\033[1;91m";
                    }
                    if (grid_[i][j].player->getRole() == KEEPER){
                        c+= "G ";
                    }
                    else if(grid_[i][j].player->getRole() == CHASER){
                        c+= "P ";
                    }
                    else if(grid_[i][j].player->getRole() == SEEKER){
                        c+= "A ";
                    }
                    else if(grid_[i][j].player->getRole() == BEATER){
                        c+= "B ";
                    }
                    c+= "\033[0m";
                    //delete grid_[i][j].player;
                }
                else{
                    c += "\u2B21 ";
                }
                
            }
            else if (grid_[i][j].type == GOAL){
                c += "\033[1;32m오\033[0m";
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
