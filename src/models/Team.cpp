#include "Team.h"

#include <iostream>
using namespace std;

Team::Team(){
    for(int i = 0; i < 7; ++ i){
        players_[i] = 0;
    }
}

Team::Team(JsonValue * json){
    JsonDict * team = JDICT(json);
    JsonDict * player_dict;
    NonFieldPlayer *players[7];

    if(team == NULL)
        throw ModelUnserializationError();
    JsonList * players_list = JLIST((*team)["players"]);
    if(players_list == NULL)
        throw ModelUnserializationError();
    if(players_list->size() != 7)
        throw ModelUnserializationError();

    for(int i = 0; i < 7; i++){
        player_dict = JDICT((*players_list)[i]);
        if(player_dict == NULL)
            players[i] = NULL;
        else{
            players[i] = new NonFieldPlayer(player_dict);
        }
    }

}

Team::Team(NonFieldPlayer *players[7]){
    for(int i = 0; i < 7; ++ i){
        players_[i] = players[i];
    }
}

Team::~Team(){}

void Team::setPlayers(NonFieldPlayer players[7]){
    for (int i = 0; i<7; ++i){
        players_[i] = &players[i];
    }
}

void Team::setPlayer(NonFieldPlayer& player,int pos){
    players_[pos] = &player;
}

NonFieldPlayer* Team::getPlayer(int pos){
    return players_[pos];
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

Team::operator JsonValue() const{
    JsonDict r;
    JsonList * players = new JsonList();
    for(int i = 0; i < 7; i++){
        if(players_[i] != NULL){
            JsonValue * item = new JsonValue(*(players_[i]));
            players->add(item);
        }
        else {
            players->add(new JsonNull());
        }
    }
    r.add("players", players);

    return r;
}
