#ifndef FIELDPLAYER_H
#define FIELDPLAYER_H

#include "Player.h"

class FieldPlayer : public Player{

    public:
        FieldPlayer();
        ~FieldPlayer();
        FieldPlayer& operator=(Player& player);
        void move();
        void hitBudger();
        void catchGoldenSnitch();
        void throwQuaffle();
        void catchQuaffle();
        void testMove();

};

#endif // FIELDPLAYER_H
