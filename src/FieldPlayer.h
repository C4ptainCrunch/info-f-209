#ifndef FIELDPLAYER_H
#define FIELDPLAYER_H

#include "Player.h"


class FieldPlayer : public Player{

    public:
        FieldPlayer(int role);
        ~FieldPlayer();
        FieldPlayer& operator=(Player& player);
        void move();
        void hitBudger();
        void catchGoldenSnitch();
        void throwQuaffle();
        void catchQuaffle();
        void testMove();
        int getRole();
    private:
        int role_;

};

#endif // FIELDPLAYER_H
