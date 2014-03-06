#ifndef FIELDPLAYER_H
#define FIELDPLAYER_H

#include "Player.h"
#include "NonFieldPlayer.h"


class FieldPlayer: public Player {

public:
    FieldPlayer(int role, bool guest);
    FieldPlayer();
    ~FieldPlayer();
    FieldPlayer(NonFieldPlayer & nonFieldPlayer, int role, bool guest);
    FieldPlayer & operator=(Player & player);
    void move();
    void hitBudger();
    void catchGoldenSnitch();
    void throwQuaffle();
    void catchQuaffle();
    void testMove();
    bool isInGuestTeam();
    int getRole();
    void setRole(int role);
private:
    bool guest_;
    int role_;

};

#endif // FIELDPLAYER_H
