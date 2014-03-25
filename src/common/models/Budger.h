#ifndef BUDGER_H
#define BUDGER_H

#include <stdlib.h>
#include <time.h>
#include <string>

#include "Position.h"
#include "Player.h"
#include "Case.h"

#include "Ball.h"

class Budger: public Ball {

public:
    Budger();
    Budger(int speed, Position position, Way hitWay);
    ~Budger();
    Position autoMove(const Case grid[WIDTH][LENGTH]);
    void isHit(const char direction, const int power, const Case grid[WIDTH][LENGTH]);
    void hitPlayer(Player * player, int power);
    std::string getName();
    Way getHitWay() const;

private:
    Way hitWay_;
};

#endif // BUDGER_H
