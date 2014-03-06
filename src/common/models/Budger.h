#ifndef BUDGER_H
#define BUDGER_H

#include "Ball.h"

#include "Position.h"
#include "Player.h"

#include "Case.h"
#include <stdlib.h>
#include <time.h>

class Budger: public Ball {

public:
    Budger();
    ~Budger();
    Position autoMove(const Case grid[WIDTH][LENGHT]);
    Way isHit(const char direction, const int power, const Case grid[WIDTH][LENGHT]);
    void hitPlayer(Player & player, int power);
};

#endif // BUDGER_H
