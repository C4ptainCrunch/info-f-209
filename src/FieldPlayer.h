#ifndef FIELDPLAYER_H
#define FIELDPLAYER_H

#include "Player.h"

class FieldPlayer : public Player{

    public:
        FieldPlayer();
        ~FieldPlayer();
        FieldPlayer operator=();
        void move();
        void hitBludger();
        void catchSnitch();
        void throwQuaffle();
        void catchQuaffle();
        void testMove();

};

#endif // FIELDPLAYER_H
