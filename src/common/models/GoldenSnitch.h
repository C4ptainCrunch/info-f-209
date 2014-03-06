#ifndef GOLDENSNITCH_H
#define GOLDENSNITCH_H

#include <stdlib.h>
#include <time.h>
#include <string>

#include "Position.h"
#include "Case.h"

#include "Ball.h"

class GoldenSnitch: public Ball {

public:
    GoldenSnitch();
    ~GoldenSnitch();
    Position autoMove(const Case grid[WIDTH][LENGTH]);
    std::string getName();
};

#endif // GOLDENSNITCH_H
