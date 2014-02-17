#ifndef TEAM_H
#define TEAM_H

#include "Player.h"
#include "NonFieldPlayer.h"

class Team{

    public:
        Team(NonFieldPlayer *players[7]);
        Team();
        ~Team();
        void setPlayers(NonFieldPlayer players[7]);
        void setPlayer(NonFieldPlayer& player, int pos);
        NonFieldPlayer* getPlayers();
        NonFieldPlayer* changePlayer(int pos, NonFieldPlayer& player);
        NonFieldPlayer & removePlayer(int pos);
        void swapPlayers(int pos1, int pos2);

    private:
        NonFieldPlayer *players_[7];
};

#endif // TEAM_H
