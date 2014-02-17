#ifndef BUDGER_H
#define BUDGER_H

#include "Ball.h"

class Budger : public Ball{

    public:
        Budger();
        ~Budger();
        Position autoMove(const Position pos);
        Position isHit(const Position pos, const char direction, const int power);
        void hitPlayer(Player& player, int power);
};

#endif // BUDGER_H
