#ifndef TEAM_H
#define TEAM_H

#include "Player.h"
#include "NonFieldPlayer.h"

class Team{

    public:
        Team();
        ~Team();
        Team operator=();
        Player& getPlayers();
        NonFieldPlayer& getNonFieldPlayers();
        void setPlayers();
        void setNonFieldPlayers();

    private:
        Player *myPlayer[ 7];
        NonFieldPlayer *myNonFieldPlayer[ 7];
};

#endif // TEAM_H
