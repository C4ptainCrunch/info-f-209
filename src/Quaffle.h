#ifndef QUAFFLE_H
#define QUAFFLE_H

#include "Ball.h"

class Quaffle : public Ball{

    public:
        Quaffle();
        ~Quaffle();
        void move();

};

#endif // QUAFFLE_H
