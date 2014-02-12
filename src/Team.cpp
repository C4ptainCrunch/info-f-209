#include "Team.h"

#include <iostream>

Team::Team(NonFieldPlayer *players[7]){
    for(int i = 0; i < 7; ++ i){
        players_[i] = players[i];
    }
}

Team::~Team(){}

NonFieldPlayer* Team::getPlayers(){
    return *players_;
}

NonFieldPlayer* Team::changePlayer(int pos, NonFieldPlayer& player){
    NonFieldPlayer *tmpPlayer = players_[pos];
    players_[pos] = &player;
    return tmpPlayer;
}

NonFieldPlayer& Team::removePlayer(int pos){
    NonFieldPlayer* tempPlayer = (players_[pos]);
    players_[pos] = NULL;
    return *tempPlayer;
}

void Team::swapPlayers(int pos1, int pos2){
    NonFieldPlayer* tempPlayer = (players_[pos1]);
    players_[pos1] = players_[pos2];
    players_[pos2] = tempPlayer;
}
