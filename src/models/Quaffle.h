#ifndef QUAFFLE_H
#define QUAFFLE_H

#include "Ball.h"
#include "Position.h"

class Quaffle : public Ball{

    public:
        Quaffle();
        ~Quaffle();
        Position thrown(const Position pos, const char direction, const int power);

};

#endif // QUAFFLE_H
