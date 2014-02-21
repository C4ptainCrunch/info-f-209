#ifndef QUAFFLE_H
#define QUAFFLE_H

#include "Ball.h"
#include "Position.h"
#include "Case.h"

class Quaffle : public Ball{

    public:
        Quaffle();
        ~Quaffle();
        Way thrown(const char direction, const int power, const Case grid[WIDTH][LENGHT]);

};

#endif // QUAFFLE_H
