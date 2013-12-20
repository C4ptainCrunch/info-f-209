#ifndef GOLDENSNITCH_H
#define GOLDENSNITCH_H

#include "Ball.h"


class GoldenSnitch : public Ball {

    public:
        GoldenSnitch();
        ~GoldenSnitch();
        GoldenSnitch operator=();
        void move();

};

#endif // GOLDENSNITCH_H
