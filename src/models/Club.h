#ifndef CLUB_H
#define CLUB_H

#include <vector>
#include "Installation.h"
#include "Team.h"
#include "NonFieldPlayer.h"

#include "../lib/json/json.h"

enum {INFIRMARY = 1, CANDYSHOP = 2, FANSHOP = 3, FIELD = 4, TRAININGFIELD = 5};


class Club {

    public:
        Club();
        Club(JsonValue * json);
        Club(int money, Installation* installations, Team& team, std::vector<NonFieldPlayer*> players);
        ~Club();

        int addMoney(const int deltaMoney);
        int getMoney();

        int getLevel();//calcule le level

        Team* getTeam();

        operator JsonValue() const;

        std::vector<NonFieldPlayer*> getNonFieldPlayers();
        void addNonFieldPlayer(NonFieldPlayer* player);
        NonFieldPlayer* removeNonFieldPlayer(unsigned int pos);

        void addInstallation(Installation& installation, int pos);
        Installation* getInstallations();


    private:
        int money_;
        Installation installations_[5];
        Team *team_ = new Team();
        std::vector<NonFieldPlayer*> players_;
};

#endif // CLUB_H
