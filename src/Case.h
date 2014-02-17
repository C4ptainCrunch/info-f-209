#ifndef CASE_H
#define CASE_H

#include "FieldPlayer.h"
#include "Ball.h"

enum { VOID = 0, USABLE = 1, GOAL = 2 };

struct Case{
    int type;
    FieldPlayer* player = 0;
    Ball* ball = 0;
};

#endif // CASE_H