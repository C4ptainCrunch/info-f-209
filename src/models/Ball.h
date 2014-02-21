#ifndef BALL_H
#define BALL_H

#include "Position.h"

class Ball {

    public:
        Ball(int speed);
        virtual ~Ball();
        Position getPosition();
        void setPosition(int x, int y);
        void setPosition(Position position);

    protected:
        int speed_;
        Position position_;
};
#endif // BALL_H
