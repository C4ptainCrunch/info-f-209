#ifndef BUDGER_H
#define BUDGER_H

#include "Ball.h"

class Budger : public Ball{

    public:
        Budger();
        ~Budger();
        void move();
        void hitPlayer();
};

#endif // BUDGER_H
