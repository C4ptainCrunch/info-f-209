#ifndef POSITION_H
#define POSITION_H

struct Position{
    unsigned int x;
    unsigned int y;
};

bool operator ==(const Position& pos1, const Position& pos2);

#endif // POSITION_H
