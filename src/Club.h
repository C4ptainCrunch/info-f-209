#ifndef CLUB_H
#define CLUB_H

#include <vector>
#include "Installation.h"
#include "Manager.h"
#include "Team.h"
#include "NonFieldPlayer.h"

class Club {

    public:
        Club();
        Club(int money, vector<Installation> installations, Team& team, vector<NonFieldPlayer> players)
        ~Club();
        int getMoney();
        int addMoney(const int deltaMoney);
        int getLevel();//calcule le level
        Team& getTeam();
        std::vector< Installation > getInstallations();
        std::vector< NonFieldPlayer > getNonFieldPlayers();
        void setTeam();
        void setInstallations();
        void addNonFieldPlayers();

    private:
        int money;
        std::vector< Installation > installations;
        Team *team;
        std::vector< NonFieldPlayer > players;
};

#endif // CLUB_H
