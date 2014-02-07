#ifndef CASE_H
#define CASE_H

#include "FieldPlayer.h"
#include "Ball.h"

enum { VOID, USABLE, GOAL };

struct Case{
    char type;
    FieldPlayer* player;
    Ball* ball;
};

#endif // CASE_H
