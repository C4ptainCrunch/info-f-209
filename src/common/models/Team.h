#ifndef TEAM_H
#define TEAM_H

#include "Player.h"
#include "NonFieldPlayer.h"
#include "../lib/json/json.h"
#include "ModelUnserializationError.h"

class Team {

public:
    Team(NonFieldPlayer * players[7]);
    Team();
    Team(JsonValue * json);
    ~Team();
    void setPlayers(NonFieldPlayer players[7]);
    void setPlayer(NonFieldPlayer & player, int pos);
    NonFieldPlayer * getPlayer(int pos);
    NonFieldPlayer * changePlayer(int pos, NonFieldPlayer & player);
    NonFieldPlayer & removePlayer(int pos);
    void swapPlayers(int pos1, int pos2);
    operator JsonValue() const;

private:
    NonFieldPlayer * players_[7];
};

#endif // TEAM_H
