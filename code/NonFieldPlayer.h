#ifndef NonFieldPlayer_h
#define NonFieldPlayer_h

#include "Player.h"

class Team;
class Club;

class NonFieldPlayer : public Player, public Player {

 public:

    virtual void getLevel();

    virtual void setExp();

    virtual void levelUp();

 private:

    virtual void Vocation();


 private:
    Integer level;
    Integer vocation;

 public:

    Team ** myTeam;

    Club ** myClub;
};

#endif // NonFieldPlayer_h
