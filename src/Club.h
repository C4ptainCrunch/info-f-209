#ifndef CLUB_H
#define CLUB_H

#include <vector>
#include "Installation.h"
#include "Team.h"
#include "NonFieldPlayer.h"

class Club {

    public:
        Club();
        Club(int money, std::vector<Installation> installations, Team& team, std::vector<NonFieldPlayer> players);
        ~Club();

        int addMoney(const int deltaMoney);
        int getMoney();

        int getLevel();//calcule le level

        Team* getTeam();

        std::vector<NonFieldPlayer> getNonFieldPlayers();
        void addNonFieldPlayer(NonFieldPlayer player);
        NonFieldPlayer& removeNonFieldPlayer(unsigned int pos);

        void addInstallation(Installation& installation);
        std::vector<Installation> getInstallations();
        Installation& delInstallation(unsigned int pos);


    private:
        int money_;
        std::vector<Installation> installations_;
        Team *team_;
        std::vector<NonFieldPlayer> players_;
};

#endif // CLUB_H
