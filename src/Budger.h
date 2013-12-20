#ifndef BUDGER_H
#define BUDGER_H

#include "Ball.h"

class Budger : public Ball{

    public:
        Budger();
        ~Budger();
        Budger operator=(const Ball &ball);
        void move();
        void hitPlayer();
};

#endif // BUDGER_H
