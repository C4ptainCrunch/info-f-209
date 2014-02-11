#ifndef CASE_H
#define CASE_H

#include "FieldPlayer.h"
#include "Ball.h"

enum { VOID = 0, USABLE = 1, GOAL = 2 };

struct Case{
    int type;
    FieldPlayer* player;
    Ball* ball;
};

#endif // CASE_H
