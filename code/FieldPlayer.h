#ifndef FieldPlayer_h
#define FieldPlayer_h

#include "Player.h"


class FieldPlayer : public Player, public Player, public Player, public Player {

 public:

    virtual void move();

    virtual void hitBludger();

    virtual void catchSnitch();

    virtual void throwQuaffle();

    virtual void catchQuaffle();

    virtual void testMove();
};

#endif // FieldPlayer_h
