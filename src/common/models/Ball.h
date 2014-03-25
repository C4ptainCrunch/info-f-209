#ifndef BALL_H
#define BALL_H

#include <string>

#include "Position.h"

class Ball {

public:
    Ball(int speed);
    Ball(int speed, Position position);
    virtual ~Ball();
    Position getPosition();
    void setPosition(int x, int y);
    void setPosition(Position position);
    std::string virtual getName() = 0;
    int getSpeed() const;

protected:
    int speed_;
    Position position_;
};
#endif // BALL_H
