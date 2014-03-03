#ifndef CASE_H
#define CASE_H

#include "FieldPlayer.h"
#include "Ball.h"
#include "Position.h"

enum { VOID = 0, USABLE = 1, GOAL = 2 };

enum { UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN_LEFT, LEFT, UP_LEFT};

typedef std::vector<Position> Way;

enum { WIDTH = 30, LENGHT = 64};

struct Case{
    int type;
    FieldPlayer* player = 0;
    Ball* ball = 0;
};

Position nextCase(Position position, int direction, const Case grid[WIDTH][LENGHT]);

#endif // CASE_H
