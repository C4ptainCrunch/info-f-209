#ifndef GOLDENSNITCH_H
#define GOLDENSNITCH_H

#include "Ball.h"
#include "Position.h"

#include "Case.h"
#include <stdlib.h>
#include <time.h>


class GoldenSnitch : public Ball {

    public:
        GoldenSnitch();
        ~GoldenSnitch();
        Position autoMove(const Case grid[WIDTH][LENGTH]);

};

#endif // GOLDENSNITCH_H
